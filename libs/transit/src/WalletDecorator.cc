#include "WalletDecorator.h"
#include "DataCollectionSingleton.h"

/**
TODO:
 ISSUES:
    * Account won't write for robot to CSV but will for drone
    * 

*/

WalletDecorator::WalletDecorator(IEntity* entity){
    std::string temp = entity->GetDetails()["type"].ToString();
    type = temp.substr(1, 5);
    this->graph = entity->getGraph();
    component = entity;
    if (type.compare("drone") == 0){
        account = 0;
    }
    else{
        account = rand()%RANGE + START_MONEY;
    }
}

IStrategy* WalletDecorator::getStrategy(IEntity* entity){
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

double WalletDecorator::getCostForTrip(IEntity* entity){
    IStrategy* strategy = getStrategy(entity);
    float dist = strategy->getTotalDistance();
    delete strategy;
    float speed = entity->GetSpeed();
    return (dist/speed)*TRIP_MULTIPLIER; // total time for trip * Cost per unit of time
}

void WalletDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    /**
     * Robots should only be charged moeny when its picked up. They pay incrementally
     * but the robot makes sure it has enough money for the whole trip
     */

    DataCollectionSingleton* dataCollection = DataCollectionSingleton::getInstance();
    
    if (type.compare("robot") == 0){
        // Client must be validated
        if (!clientValid && !GetAvailability()){
            double costForTrip = getCostForTrip(this);
            // transfer money when robot is picked up
            if (account - costForTrip < 0){
                SetAvailability(true);        // Make robot avail if not enough money
                clientValid = false;          // Client is not valid
            }
            else {
                account -= costForTrip;
                clientValid = true;
                dataCollection->writeAccountInfo(component->GetId(), account);
                std::cout << "write account for robot\n";

                // std::cout << "getID in walletDecorator: " << component->GetId()+1 << "; Account: " << account << std::endl;
            }
        }
        else if (clientValid && GetPickedUp() && GetPosition().Distance(GetDestination()) < 4.0){
            clientValid = false;
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
    if (type.compare("drone") == 0){
        // Drone is at a recharge station charging
        if (GetChargingStatus()){
            // Drone pays for recharge per dt if they are at a recharge station
            if (account - COST_FOR_RECHARGE*dt >= 0){
                account -= COST_FOR_RECHARGE*dt;
                std::cout << "Wallet (Drone), Drone Recharging (Payed)\n";
            }
             // Drone can't charge if it doesnt have enough money, so charging status changed
            else {
                SetChargingStatus(false);
                std::cout << "Wallet (Drone), Drone can't afford Recharge\n";
            }
        }

        // If either are avaible then the trip should be canceled
        else if (GetEntity() != nullptr && (GetAvailability() || GetEntity()->GetAvailability())){
            SetAvailability(true);
            GetEntity()->SetAvailability(true);
            clientValid = false;
        }
        // Determine if the client is present
        else if (GetEntity() != nullptr){
            // Determines if drone should be payed
            if (GetEntity()->GetPickedUp() && clientValid && !GetAvailability()){
                dataCollection->writeAccountInfo(component->GetId(), account);
            }

            // Determines if trip or pick up is completef
            if (GetPosition().Distance(GetDestination()) < 4.0){
                // Determines when client is picked up
                if (!GetEntity()->GetPickedUp() && !clientValid){
                    clientValid = true;
                    account += getCostForTrip(GetEntity());
                }
            }
        }
        // Determines when client is dropped off (nearest entity null in drone:update when dropped off)
        else if(GetEntity() == nullptr && GetAvailability()) { 
            clientValid = false;
        }
    }
    component->Update(dt, scheduler);
}