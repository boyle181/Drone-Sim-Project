#include "WalletDecorator.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "graph.h"
#include "Drone.h"
#include "Robot.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

WalletDecorator::WalletDecorator(IEntity* entity){
    type = (entity->GetDetails())["type"].ToString();
    if (type.compare("drone") == 0){
        this->account = 0;
        worker = dynamic_cast<Drone*>(component);
    }
    else{
        this->account = rand()%RANGE + START_MONEY;
    }
}

double WalletDecorator::getAccount(){
    return this->account;
}
void WalletDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    /**
     * Robots should only be charged moeny when its picked up. They pay incrementally
     * but the drone makes sure they have enough money for the whole trip
     */
     Robot* client;
     
    if (type.compare("robot") == 0){
        client = dynamic_cast<Robot*>(component);
        if(client->GetPickedUp()) {
            account -= COST_FOR_TRIP;
        }
    }
    /**
     * Drone:
     * (*) Drone needs to be aware of when its recharging so then 
     *     it can pay when it is
     * (*) Drone needs to pay when it is recharging
     * (*) Drone needs to be able to calcuate the cost of path
     * (*) Drone needs to access the account of the robot to 
     *     determine if the robot can get a ride
     * 
     * Functions needed:
     *  GetChargingStatus()     -> so drone knows when its recharging
     *  GetToFinalDestination() -> returns the strategy pattern
     *  IsPickedUp()            ->  robot should be aware of 
     *                             when the robot has been picked up
     *  GetEntity()             -> returns the entity being considered 
     *                             for a trip
     */
    if (type.compare("drone") == 0 && !worker){
        IStrategy* strategy = worker->GetToFinalDestination();
        if (worker->GetChargingStatus()){ // Drone pays for recharge per dt
            account -= COST_FOR_RECHARGE;
        }
        // Determine if the entity present is able to afford the trip
        if (!clientValid && strategy != nullptr){ // Note: Strategy will be nullptr if theres no nearest entity
            float dist = strategy->getTotalDistance();
            float speed = worker->GetSpeed();

            // Total time taken for the trip adjusted by Cost_for_trip
            float paymentForTrip = (dist/speed)*COST_FOR_TRIP;
            if (!this->getAccount() - paymentForTrip >= 0){
                worker->SetAvailability(true);
                clientValid = false;
            }
            else {
                clientValid = true;
            }
        }
        // When the trip is complete a new client will be selected
        if (strategy->IsCompleted()){
            clientValid = false;
        }
    }
    component->Update(dt, scheduler);
}