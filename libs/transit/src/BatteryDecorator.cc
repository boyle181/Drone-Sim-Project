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
    this->maxCapacity = 100;
}
void BatteryDecorator::recharge(int amount){
    this->currentCapacity += amount;
}
bool BatteryDecorator::usage(int amount){
    return !(amount > this->maxCapacity);
}
int BatteryDecorator::getcurrentCapacity(){
    return this->currentCapacity;
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    // TODO: Correct this later on to account for the whole trip
    // we need to figure how to get tripCost value
    int tripCost = 1000; // either total time it takes or total trip distance
    
    // convert time it takes to how much total battery it will utilize
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
    if(!component->getAvailability() && canUpdateBattery){ // go to recharge station
        currentCapacity -= dt; // Battery should always dec as drone moves
    } 
    else if (currentCapacity < 50) // drone is not moving at all
        // go to recharge station
    }
    

    // bool updateBattery;
    // Drone *drone = (Drone*)component;
    // if(drone->pickedUp) {
    //     updateBattery = this->usage(10);
    //     if(!updateBattery) {

    //     }
    // }
    // // update battery percentage
    // if(drone->toFinalDestination->isCompleted()) {

    // }

    
    // calculate the distance of entire trip to determine if drone can fulfil the trip with current batter level
    // we want to get time of trip = distance / speed
    // 2 distances: drone -> robot, drone+robot -> final destination
    
    // check for nearest entity path strategy being used
    // IStrategy* strategy;
    // std::vector<float> path;
    // if(nearestEntity(component).GetStrategy() == "astar") {
    //     strategy = new AstarStrategy(destination, finalDestination, component->graph); // creating this object will set the path variable
    //     path = (PathStrategy*)strategy->path;
    // }
    // if(nearestEntity(component).GetStrategy() == "dfs") {
    //     strategy = new DfsStrategy(destination, finalDestination, component->graph);
    //     path = (PathStrategy*)strategy->path;
    // if(nearestEntity(component).GetStrategy() == "dijkstra") {
    //     strategy = new DijkstraStrategy(destination, finalDestination, component->graph);
    //     path = (PathStrategy*)strategy->path;
    // }
    // use GetPath(std::vector<float> src, std::vector<float> dest, const RoutingStrategy& pathing) which returns a vector of floats
    // loop over the floats to calculate the distance of each path strategy
    
    // Distance from robots destination -> final destination

    //  g->GetPath(start, end, Dijkstra::Instance());

    // std::vector< std::vector<float> > path = component->graph->GetPath(start, end, Dijkstra::Instance());
    // std::vector< std::vector<float> > path = component->getNearestEntity(component)->graph->GetPath();
    // for (int i = 0; i<path.size()-1; i++){
    //     // Vector3 point1 = Vector(path[0][0], , ) 
    // }

    // Drone to robot and robot to drone, calc distance for entire trip
    // Then determine battery usage by total time that the trip will take
    // if not find nearest recharge station. Set not avaible when going to
    // a recharge station.

    // figure out how many pixels 
    
} 