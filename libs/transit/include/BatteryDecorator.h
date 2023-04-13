#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntity.h"
class BatteryDecorator : public IEntity {

 public:
    BatteryDecorator(IEntity* entity);
    void recharge(int amount);
    bool usage(int amount);
    int getPercentage();
 private:
    IEntity* component;
    int percentage;
};

#endif  