#include "WalletDecorator.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
WalletDecorator::WalletDecorator(IEntity* entity){
    this->account = rand()%1000 + 1;
}
WalletDecorator::addMoney(double money){
    this->account += money;
}
WalletDecorator::subtractMoney(double money){
    if (money > this->account){
        return false;
    } 
    else{
        this->account -= money;
        return true;
    }
}
WalletDecorator::getAccount(){
    return this->account;
}