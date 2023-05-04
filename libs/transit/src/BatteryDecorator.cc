#include "BatteryDecorator.h"
#include "DataCollectionSingleton.h"

BatteryDecorator::BatteryDecorator(IEntity* entity){
    this->component = entity;
    currentCapacity = maxCapacity;
    this->graph = entity->getGraph();
}
void BatteryDecorator::recharge(double amount){
    this->currentCapacity += amount;
}

bool BatteryDecorator::hasEnoughBattery(double amount){
    return !(amount > this->currentCapacity);
}

void BatteryDecorator::getNearestRechargeStation(std::vector<IEntity*> scheduler) {
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
    if (nearestRechargeStation != NULL){
        SetEntity(nullptr);
        SetAvailability(false);
        nearestRechargeStation->SetAvailability(false);
        SetGoingToRecharge(true);
        SetDestination(nearestRechargeStation->GetPosition());
        toRechargeStation = new BeelineStrategy(GetPosition(), nearestRechargeStation->GetPosition());
    }
}

double BatteryDecorator::getTripBatteryCost(IEntity* entity) {
    // make sure we are passing a robot
    IStrategy* strategy = getStrategy(entity);
    float dist = strategy->getTotalDistance();
    delete strategy;
    return dist * BATTERY_MULTIPLIER;
}

IStrategy* BatteryDecorator::getStrategy(IEntity* entity){
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

/**
Battery Logic:
    - Calculate if the trip is possible given the current battery that the component has
        - Not Enough, Cancel trip and go to recharge station
            - Change nearest entity to a recharge station
            - Set the recahrge when its at a recharge station
            - Charge until full
            - Change recharge status when full and change avail
        - Enough, continue with everything unchanged
    - 
*/

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    
    DataCollectionSingleton* dataCollection = DataCollectionSingleton::getInstance();
    // *** Checks if drone is on a trip (if an entity has been assign for pick up) ***
    if(GetEntity() != nullptr) {
        if(!clientValid) {
            double totalTripBatteryUsage = getTripBatteryCost(GetEntity());
            canUpdateBattery = hasEnoughBattery(totalTripBatteryUsage);
            std::cout << "Total trip battery cost: " << totalTripBatteryUsage << std::endl;
            std::cout << "Can it update battery: " << canUpdateBattery << std::endl;
            std::cout << "Is drone available: " << GetAvailability() << std::endl;
            writeCSV = false;
            clientValid = true;
        }
        if (!GetAvailability() && canUpdateBattery){
            // std::cout << "Using Battery\n";
            currentCapacity -= BATTERY_MULTIPLIER*dt;
            // std::cout << "Battery Level: " << currentCapacity << std::endl;
            dataCollection->writeBatteryUsage(GetId(), currentCapacity);
        }

        // Case when drone is available, but does not have enough battery to complete trip for robot
        if (!GetAvailability() && !canUpdateBattery && !GetGoingToRecharge()){
            getNearestRechargeStation(scheduler); // get the recharge station that the drone will go
            std::cout << "Not enough battery to complete trip, going to recharge station!" << std::endl;
        }        
    }
    
    // *** When trip is complete, clientValid and writeCSV reset ***
    if(!writeCSV && GetEntity() == nullptr && GetAvailability()) {
        clientValid = false;
        writeCSV = true;
    }

    // *** Drone is going towards recharge station ***
    if (toRechargeStation != NULL){
        toRechargeStation->Move(this, dt);
        if (toRechargeStation->IsCompleted()) {
            std::cout << "inside toRechargeStation->IsCompleted()" << std::endl;
            delete toRechargeStation;
            toRechargeStation = NULL;
            SetAvailability(true);
            nearestRechargeStation->SetAvailability(true);
            SetChargingStatus(true);
        }
    }

    // *** Drone is recharging stops once maxCapacity is reached ***
    if (GetChargingStatus()){
        std::cout << "at charging station\n";
        if (currentCapacity < maxCapacity) {
            std::cout << "Charging Battery\n";
            currentCapacity += RECHARGE_RATE*dt;
            std::cout << "Battery Level: " << currentCapacity << std::endl;
        } else if (currentCapacity >= maxCapacity || !GetChargingStatus()){
            std::cout << "max battery reached\n";
            SetChargingStatus(false);
            SetAvailability(true);
            SetGoingToRecharge(false);
        }
    }
    component->Update(dt, scheduler);
} 