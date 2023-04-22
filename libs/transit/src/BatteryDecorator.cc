#include "BatteryDecorator.h"
#include "IEntity.h"
#include "Drone.h"
#include "IStrategy.h"
#include "graph.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

BatteryDecorator::BatteryDecorator(IEntity* entity){
    this->component = entity;
    int currentCapacity = maxCapacity;

}
void BatteryDecorator::recharge(double amount){
    this->currentCapacity += amount;
}
bool BatteryDecorator::usage(double amount){
    return !(amount > this->maxCapacity);
}
int BatteryDecorator::getcurrentCapacity(){
    return this->currentCapacity;
}

void BatteryDecorator::getNearestRechargeStation(std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
    for (auto entity : scheduler) {
        std::string type = entity->GetDetails()["type"];
        if (entity->GetAvailability() && type.compare("rechargeStation") == 0) {
            float disToEntity = entity->GetPosition().Distance(entity->GetPosition());
            if (disToEntity <= minDis) {
                minDis = disToEntity;
                nearestRechargeStation = (RechargeStation*)entity;
            }
        }
    }
};

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    // TODO: Correct this later on to account for the whole trip
    // we need to figure how to get tripCost value
    int tripCost = 1000; // either total time it takes or total trip distance
    
    // convert time it takes to how much totals battery it will utilize
    int totalBatteryUsage;

    bool canUpdateBattery = usage(totalBatteryUsage);

    // scenarios:
    // drone is available to pick up robot -> battery should not be changed since it is not moving
    // drone is not available (it is moving to robot destination) -> battery should be updated


    if(!canUpdateBattery) {
        // set drone to available
        // drone should go to recharge station
    }

    // drone is moving
    if(!component->GetAvailability() && canUpdateBattery) { // go to recharge station
        currentCapacity -= dt; // Battery should always dec as drone moves
    } 
    else if (currentCapacity < 50) { // drone is not moving at all
        // go to recharge station
    }
    
    
} 