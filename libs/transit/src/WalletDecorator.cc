#include "WalletDecorator.h"
#include "DataCollectionSingleton.h"

/**
 * Robot gets pays correctly but drone doesn't get paid correctly
 * Account for robot isn't be outputted properly to csv
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

IStrategy* WalletDecorator::getStrategy(){
    std::string strategyName = component->GetStrategyName();
    Vector3 position = component->GetPosition();
    Vector3 destination = component->GetDestination();
    if (strategyName.compare("astar") == 0) {
        return new AstarStrategy(position, destination, graph);
    } else if (strategyName.compare("dfs") == 0) {
        return new DfsStrategy(position, destination, graph);
    } else if (strategyName.compare("dijkstra") == 0) {
        return new DijkstraStrategy(position, destination, graph);
    }
    return new BeelineStrategy(position, destination);
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
            IStrategy* strategy = getStrategy();
            float dist = strategy->getTotalDistance();
            delete strategy;
            float speed = GetSpeed();
            float paymentForTrip = (dist/speed)*COST_FOR_TRIP; // total time for trip * Cost per unit of time
            std::cout << "Wallet: (Robot), cost of trip\n" << paymentForTrip;
            if (account - paymentForTrip < 0){
                SetAvailability(true);        // Make robot avail if not enough money
                clientValid = false;          // Client is not valid
                std::cout << "Wallet: (Robot), Robot doesn't have enough money\n";
            }
            else {
                clientValid = true;
                account -= paymentForTrip;
                std::cout << "Wallet: (Robot), Robot has enough money\n";
            }
        }
        // If the client is validated and already picked up then they will be charged
        // if(clientValid && GetPickedUp()) {
        //     account -= COST_FOR_TRIP;
        //     std::cout << "Wallet (Robot), Paid for trip\n";
        // }
        else if (clientValid && GetPickedUp() && GetPosition().Distance(GetDestination()) < 4.0){
            clientValid = false;
            std::cout << "Wallet (Robot), Trip Complete\n";
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
            if (account - COST_FOR_RECHARGE >= 0){
                account -= COST_FOR_RECHARGE;
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
            std::cout << "Wallet (Drone), Trip not scheduled\n";
        }
        // Determine if the client is present
        else if (GetEntity() != nullptr){
            // Determines if drone should be payed
            if (GetEntity()->GetPickedUp() && clientValid && !GetEntity()->GetAvailability()){ // FIX THIS, never works
                account += COST_FOR_TRIP;
                std::cout << "Wallet (Drone), Drones been payed\n";
            }
            // Determines if trip or pick up is complete
            if (GetPosition().Distance(GetDestination()) < 4.0){
                // Determines when client is picked up
                if (!GetEntity()->GetPickedUp()){
                    clientValid = true;
                    std::cout << "Wallet (Drone), Picked up client!\n";
                }
                // Determines when client is dropped off
                else {
                    clientValid = false;
                    std::cout << "Wallet (Drone), Trip Completed\n";
                }
            }
        }
    }
    std::cout << "Account of Entity " << GetId() << ": " << account << std::endl;
    dataCollection->writeAccountInfo(component, account); // this will only work for now but when battery is wrapped it may produce issues
    component->Update(dt, scheduler);
}