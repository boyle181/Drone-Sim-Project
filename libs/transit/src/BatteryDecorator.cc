// Copyright 2023 Jason Paciorek, Aidan Boyle, Rebecca Hoff, Nuh Misirli

#include "BatteryDecorator.h"

#include "DataCollectionSingleton.h"

BatteryDecorator::BatteryDecorator(IEntity* entity) {
  this->component = entity;
  currentCapacity = maxCapacity;
  this->graph = entity->getGraph();
}

bool BatteryDecorator::hasEnoughBattery(double amount) {
  return !(amount > this->currentCapacity);
}

void BatteryDecorator::getNearestRechargeStation(
    std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    std::string type = entity->GetDetails()["type"];
    if (type.compare("rechargeStation") == 0) {
      float disToEntity = GetPosition().Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestRechargeStation = entity;
      }
    }
  }
  if (nearestRechargeStation != NULL) {
    GetEntity()->SetAvailability(true);
    SetAvailability(false);
    nearestRechargeStation->SetAvailability(false);
    SetGoingToRecharge(true);
    Vector3 tempRechargeStation = nearestRechargeStation->GetPosition();
    Vector3 rechargeStation(tempRechargeStation[0], component->GetPosition()[1],
                            tempRechargeStation[2]);
    SetDestination(rechargeStation);
    toRechargeStation = new BeelineStrategy(GetPosition(), rechargeStation);
  }
}

double BatteryDecorator::getTripBatteryCost(IEntity* entity) {
  // make sure we are passing a robot
  IStrategy* strategy = getStrategy(entity);
  float dist = strategy->getTotalDistance();
  delete strategy;
  return dist * BATTERY_MULTIPLIER;
}

IStrategy* BatteryDecorator::getStrategy(IEntity* entity) {
  std::string strategyName = entity->GetStrategyName();
  Vector3 position = entity->GetPosition();
  Vector3 destination = entity->GetDestination();
  if (strategyName.compare("astar") == 0) {
    return new AstarStrategy(position, destination, graph);
  } else if (strategyName.compare("dfs") == 0) {
    return new DfsStrategy(position, destination, graph);
  } else if (strategyName.compare("dijkstra") == 0) {
    return new DijkstraStrategy(position, destination, graph);
  }
  return new BeelineStrategy(position, destination);
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler) {
  DataCollectionSingleton* dataCollection =
      DataCollectionSingleton::getInstance();
  // *** Checks if drone is on a trip (if an entity has been assign for pick up)
  // ***
  if (GetEntity() != nullptr) {
    if (!clientValid) {
      totalTripBatteryUsage = getTripBatteryCost(GetEntity());
      canUpdateBattery = hasEnoughBattery(totalTripBatteryUsage);
      writeCSV = false;
      clientValid = true;
    }
    if (!GetAvailability() && canUpdateBattery) {
      dataCollection->writeBatteryUsage(GetId(), currentCapacity);
    }

    if (!GetAvailability() && !canUpdateBattery && !GetGoingToRecharge() &&
        !GetChargingStatus()) {
      getNearestRechargeStation(
          scheduler);  // get the recharge station that the drone will go
    }
  }

  // *** When trip is complete, clientValid and writeCSV reset ***
  if (!writeCSV && GetEntity() == nullptr && GetAvailability()) {
    clientValid = false;
    writeCSV = true;
    currentCapacity -= totalTripBatteryUsage;
  }

  // *** Drone is going towards recharge station ***
  if (toRechargeStation != NULL) {
    toRechargeStation->Move(this, dt);
    if (toRechargeStation->IsCompleted()) {
      delete toRechargeStation;
      toRechargeStation = NULL;
      SetAvailability(false);
      nearestRechargeStation->SetAvailability(false);
      SetChargingStatus(true);
      clientValid = false;
    }
  }

  // *** Drone is recharging stops once maxCapacity is reached ***
  if (GetChargingStatus()) {
    if (currentCapacity < maxCapacity) {
      currentCapacity += RECHARGE_RATE * dt;
    } else {
      SetChargingStatus(false);
      SetAvailability(true);
      SetGoingToRecharge(false);
      nearestRechargeStation->SetAvailability(true);
      nearestRechargeStation = NULL;
    }
  }
  component->Update(dt, scheduler);
}
