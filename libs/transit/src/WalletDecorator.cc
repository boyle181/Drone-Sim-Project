#include "WalletDecorator.h"
#include "DataCollectionSingleton.h"


WalletDecorator::WalletDecorator(IEntity* entity){
    std::string temp = entity->GetDetails()["type"].ToString();
    type = temp.substr(1, 5);
    component = entity;
    if (type.compare("drone") == 0){
        account = 0;
    }
    else{
        account = rand()%RANGE + START_MONEY;
    }
}

IStrategy* WalletDecorator::getStrategy(){
    std::string strategyName = component->GetStrategyName();
    IStrategy* strategy;
    Vector3 position = component->GetPosition();
    Vector3 destination = component->GetDestination();
    if (strategyName == "astar") {
        strategy = new AstarStrategy(position, destination, graph);
    } else if (strategyName == "dfs") {
        strategy = new DfsStrategy(position, destination, graph);
    } else if (strategyName == "dijkstra") {
        strategy = new DijkstraStrategy(position, destination, graph);
    } else {
        strategy = new BeelineStrategy(position, destination);
    }
    return strategy;
}

void WalletDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    /**
     * Robots should only be charged moeny when its picked up. They pay incrementally
     * but the drone makes sure they have enough money for the whole trip
     */

    // if(pickUpDestination.Distance(component->GetDestination()) != 0) {
    //     float x = (component->GetDestination())[0];
    //     float y = (component->GetDestination())[1];
    //     float z = (component->GetDestination())[2];
    //     finalDestination = Vector3(x, y, z);
    // }

    DataCollectionSingleton* dataCollection = DataCollectionSingleton::getInstance();

    if (this->type.compare("robot") == 0){
        // Client must be validated
        if (!clientValid && !GetAvailability()){
            // IStrategy* strategy = getStrategy();
            // float dist = strategy->getTotalDistance();
            float dist = 0;
            float speed = GetSpeed();

            float paymentForTrip = (dist/speed)*COST_FOR_TRIP; // total time for trip * Cost per unit of time
            if (account - paymentForTrip < 0){
                SetAvailability(true);        // Make robot avail if not enough money
                clientValid = false;          // Client is not valid
                std::cout << "Wallet: (robot), doesn't have enough money\n";
            }
            else {
                clientValid = true;
                std::cout << "Wallet: (robot), Client has enough money\n";
            }
            // delete strategy;
        }
        // If the client is validated and already picked up then they will be charged
        if(clientValid && GetPickedUp() && !GetAvailability()) {
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
    if (this->type.compare("drone") != 0){
        // Drone is at a recharge station charging
        if (component->GetChargingStatus()){
            // Drone pays for recharge per dt if they are at a recharge station
            if (this->account - COST_FOR_RECHARGE >= 0){
                this->account -= COST_FOR_RECHARGE;
            }
             // Drone can't charge if it doesnt have enough money, so charging status changed
            else {
                component->SetChargingStatus(false);
            }
        }
        // If either are avaible then the trip should be canceled
        if (GetEntity() != nullptr && GetEntity()->GetAvailability()){
            GetEntity()->SetAvailability(true);
            clientValid = false;
            std::cout << "Wallet: (drone), Trip not scheduled\n";
        }
        // Determine if the entity present is able to afford the trip
        if (GetEntity() != nullptr){
            if (GetEntity()->GetPickedUp() && clientValid && !GetAvailability()){
                account += COST_FOR_TRIP;
                std::cout << "Wallet: (drone), Drones been payed\n";
            }
            // Trip is either complete or pick up is complete
            if (GetPosition().Distance(GetDestination()) < 4.0){
                // Determines when client is picked up
                if (!GetEntity()->GetPickedUp()){
                    GetEntity()->SetPickedUp(true);
                    std::cout << "Picked up client!\n";
                }
                // Determines when whole trip is complete
                if (GetEntity()->GetPickedUp()){
                    clientValid = false;

                    std::cout << "Trip Completed\n";
                }
            }
        }
    }
    dataCollection->writeAccountInfo(component, this->account);
    component->Update(dt, scheduler);
}