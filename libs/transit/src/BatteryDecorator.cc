#include "BatteryDecorator.h"
#include "DataCollectionSingleton.h"

BatteryDecorator::BatteryDecorator(IEntity* entity){
    this->component = entity;
    int currentCapacity = maxCapacity;
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
        if (entity->GetAvailability() && type.compare("rechargeStation") == 0) {
            float disToEntity = entity->GetPosition().Distance(entity->GetPosition());
            if (disToEntity <= minDis) {
                minDis = disToEntity;
                nearestRechargeStation = entity;
            }
        }
    }
    if (nearestRechargeStation != NULL){
        component->SetEntity(nearestRechargeStation);
        component->SetAvailability(false);
        nearestRechargeStation->SetAvailability(false);
        component->SetDestination(nearestRechargeStation->GetPosition());
        toRechargeStation = new BeelineStrategy(component->GetPosition(), nearestRechargeStation->GetPosition());
        std::cout << "Drone is going towards a recharge station" << std::endl;
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

    // check if drone has enough battery before accepting a trip
    if(GetEntity() != nullptr) {
        double totalTripBatteryUsage = getTripBatteryCost(component->GetEntity());
        bool canUpdateBattery = hasEnoughBattery(totalTripBatteryUsage) && currentCapacity != maxCapacity;
        std::cout << "Get entity found" << std::endl;

        if (!canUpdateBattery){
            getNearestRechargeStation(scheduler); // get the recharge station that the drone will go
            std::cout << "Not enough battery to complete trip, going to recharge station!" << std::endl;
        }
    }

    // check if drone is going to recharge station next, move drone to station
    if (toRechargeStation != NULL){
        std::cout << "check if drone is going to recharge station next" << std::endl;
        toRechargeStation->Move(this, dt);
        std::cout << "after move" << std::endl;
        if (toRechargeStation->IsCompleted()) {
            std::cout << "inside toRechargeStation->IsCompleted()" << std::endl;
            delete toRechargeStation;
            toRechargeStation = NULL;
            this->SetChargingStatus(true);
        }
    }

    // Entity is recharging and has to gain battery and determine if it should become aval
    if (this->GetChargingStatus()){
        std::cout << "at charging station\n";
        if (currentCapacity <= maxCapacity) {
            std::cout << "Updating Battery\n";
            currentCapacity += RECHARGE_RATE*dt;
        } else {
            std::cout << "max battery reached\n";
            this->SetChargingStatus(true);
            component->SetAvailability(true);
        }
    }
    component->Update(dt, scheduler);
} 