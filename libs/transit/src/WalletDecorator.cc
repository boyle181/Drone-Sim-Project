#include "WalletDecorator.h"
#include "DataCollectionSingleton.h"


WalletDecorator::WalletDecorator(IEntity* entity){
    this->type = entity->GetDetails()["type"].ToString();
    this->component = entity;
    this->pickUpDestination = component->GetDestination();
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

    if(pickUpDestination != component->GetDestination()) {
        finalDestination = component->GetDestination();
    }

    DataCollectionSingleton* dataCollection = DataCollectionSingleton::getInstance();
    // std::cout << "updating wallet:" << type << std::endl;
    if (this->type.compare("robot") == 0){
        std::cout << "type:" << type << std::endl;
        // If the client is not valid then they will be set to available and the drone will see this
        if (!this->clientValid){
            IStrategy* strategy = getStrategy();
            float dist = strategy->getTotalDistance();
            float speed = this->GetSpeed();

            // Total time taken for the trip adjusted by Cost_for_trip
            float paymentForTrip = (dist/speed)*COST_FOR_TRIP;
            if (!(this->account - paymentForTrip >= 0)){
                this->SetAvailability(true);        // Make drone avail if client is broke
                clientValid = false;
                std::cout << "Wallet: (robot), doesn't have enough money\n";
            }
            else {
                clientValid = true;
                std::cout << "Wallet: (robot), Client has enough money\n";
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
    if (this->type.compare("drone") != 0){
        // std::cout << "type:" << type << std::endl;
        if (component->GetChargingStatus()){ // Drone pays for recharge per dt if they are at a recharge station
            if (this->account - COST_FOR_RECHARGE >= 0){
                this->account -= COST_FOR_RECHARGE;
            }
            else { // Drone can't charge if it doesnt have enough money, so charging status changed
                component->SetChargingStatus(false);
            }
        }
        // Determine if the entity present is able to afford the trip
        if (this->GetEntity() != nullptr){
            if (!this->clientValid && pickUpDestination.Distance(this->GetDestination()) != 0){
                // cleints availabiity will be changed (above) to indicate the robot doesn't have enough money
                if (this->GetEntity()->GetAvailability()){
                    this->SetAvailability(true);
                    this->clientValid = false;
                    std::cout << "Wallet: (drone), Client doesn't have enough money\n";
                }
                else {
                    this->clientValid = true;
                    std::cout << "Wallet: (drone), Client has enough money\n";
                }
            }
            // If client is valid the drone will earn money
            else if (this->clientValid && pickUpDestination.Distance(this->GetDestination()) != 0){
                account += COST_FOR_TRIP;
            }
            // When the trip is complete a new client will be selected
            if (this->GetPosition().Distance(pickUpDestination) < 4.0){
                clientValid = false;
                std::cout << "Picked up client!\n";
            }
            if (this->GetPosition().Distance(finalDestination) < 4.0){
                clientValid = false;
                std::cout << "Trip Completed\n";
            }
        }
    }
    dataCollection->writeAccountInfo(this, this->account);
    // std::cout << "account updated of " + type << std::endl;
    component->Update(dt, scheduler);
}