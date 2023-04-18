#include "WalletDecorator.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "graph.h"
#include "Drone.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

WalletDecorator::WalletDecorator(IEntity* entity){
    std::string type = (entity->GetDetails())["type"];
    if (type.compare("drone") == 0){
        this->account = 0;
    }
    else{
        this->account = rand()%1000 + 1001;
    }
}
void WalletDecorator::payDebt(){
    this->account -= debt;
}
double WalletDecorator::getAccount(){
    return this->account;
}
void WalletDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    std::string type = (component->GetDetails())["type"];

    // TODO: Need to a rejection mechanism for insufficent funds for robots picked up
    // TODO: Lastly, write account data to singleton. Use getInstance() and the write functions on the instance
    // if (type.compare("drone") && (component->getEntity())){
    //     component->nearestEntity;
    // }

    // if (type.compare("drone") && component->toFinalDestination->IsCompleted()) { // Short circuit eval ensures this will be a drone
    //     double cost = component->GetPosition().Distance(component->GetDestination()) * 0.05; // Drone's cost for a ride
    //     this->addMoney(cost);               // Drone's money is updated
    //     component->nearestEntity->subtractMoney(cost); // Client who's picked up
    // }
    if (type.compare("robot") == 0){

    }
    if (type.compare("drone") == 0 && ((Drone*)component)->getStrategtFinalDestination()->IsCompleted()){
        account += pathTripDistance;
    }
    component->Update(dt, scheduler);
}