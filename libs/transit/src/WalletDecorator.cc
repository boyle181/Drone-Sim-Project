#include "WalletDecorator.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "graph.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

WalletDecorator::WalletDecorator(IEntity* entity){
    std::string type = (entity->GetDetails())["type"];
    if (type.compare("drone")){
        this->account = 0;
    }
    else{
        this->account = rand()%1000 + 1;
    }
}
void WalletDecorator::addMoney(double money){
    this->account += money;
}
bool WalletDecorator::subtractMoney(double money){
    if (money > this->account){
        return false;
    } 
    this->account -= money;
    return true;
}
double WalletDecorator::getAccount(){
    return this->account;
}
void WalletDecorator::Update(double dt, std::vector<IEntity*> scheduler){
    float threshold = .001;
    std::string type = (component->GetDetails())["type"];

    // TODO: Need to a rejection mechanism for insufficent funds for robots picked up
    // TODO: Lastly, write account data to singleton. Use getInstance() and the write functions on the instance
    

    // Determines distance to to figure out if money should be exchanged
    if ((component->GetPosition()).Distance(component->GetDestination()) < threshold){
        double cost = component->GetPosition().Distance(component->GetDestination()) * 0.05; // cost of ride

        // This will exchange the money between the drone and robot.
        // The sim model will call update for the drone and the robot 

        if (type.compare("drone")) {
            this->addMoney(cost);
        }
        else if (type.compare("robot")) {
            this->subtractMoney(cost);
        }
    }
    component->Update(dt, scheduler);
}