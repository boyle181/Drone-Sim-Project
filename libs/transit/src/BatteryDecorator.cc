#include "BatteryDecorator.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
BatteryDecorator::BatteryDecorator(IEntity* entity){
    this->percentage = rand()%1000 + 1;
}
BatteryDecorator::recharge(int amount){
    this->percentage += amount;
}
BatteryDecorator::usage(double amount){
    if (amount > this->percentage){
        return false;
    } 
    else{
        this->percentage -= amount;
        return true;
    }
}
BatteryDecorator::getPercentage(){
    return this->percentage;
}