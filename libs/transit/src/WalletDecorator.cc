#include "WalletDecorator.h"
#include "DataCollectionSingleton.h"


WalletDecorator::WalletDecorator(IEntity* entity){
    type = entity->GetDetails()["type"].ToString();
    this->component = entity;
    if (type.compare("drone") == 0){
        this->account = 0;
    }
    else{
        this->account = rand()%RANGE + START_MONEY;
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
    DataCollectionSingleton* dataCollection = DataCollectionSingleton::getInstance();

    if (type.compare("robot") == 0){
        // If the client is not valid then they will be set to available and the drone will see this
        if (!this->clientValid){
            IStrategy* strategy = getStrategy();
            float dist = strategy->getTotalDistance();
            float speed = this->GetSpeed();

            // Total time taken for the trip adjusted by Cost_for_trip
            float paymentForTrip = (dist/speed)*COST_FOR_TRIP;
            if (!(this->account - paymentForTrip >= 0)){
                this->SetAvailability(true);
                clientValid = false;
            }
            else {
                clientValid = true;
            }
            delete strategy;
        }
        // If the client is validated then they will be charged
        if(this->GetPickedUp() && this->clientValid) {
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
    if (type.compare("drone") == 0){
        if (component->GetChargingStatus()){ // Drone pays for recharge per dt if they are at a recharge station
            if (this->account - COST_FOR_RECHARGE >= 0){
                this->account -= COST_FOR_RECHARGE;
            }
            else { // Drone can't charge if it doesnt have enough money, so charging status changed
                component->SetChargingStatus(false);
            }
        }
        // Determine if the entity present is able to afford the trip
        if (this->GetEntity()){
            if (!clientValid){
                // cleints availabiity will be changed (above) to indicate the robot doesn't have enough money
                if (this->GetEntity()->GetAvailability()){
                    this->SetAvailability(true);
                    clientValid = false;
                }
                else {
                    clientValid = true;
                }
            }
            // If client is valid the drone will earn money
            else {
                account += COST_FOR_TRIP;
            }
            // When the trip is complete a new client will be selected
            if (this->GetPosition().Distance(this->GetDestination()) < 4.0){
                clientValid = false;
            }
        }
    }
    dataCollection->writeAccountInfo(component, this->account);
    component->Update(dt, scheduler);
}