#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntity.h"

/**
 * @brief this class inherits from the IStrategy class. 
 * It is used to create changeable and trackable batteries inside drones.
 */
class BatteryDecorator : public IEntity {

 public:

  /**
   * @brief battery is created with a random preset battery percentage
   * @param entity a pointer IEntity object in which the battery is created
   */
   BatteryDecorator(IEntity* entity);

  /**
   * @brief Recharges battery by adding more to the battery percentage over time
   * @param amount An int which is added to the total battery percentage
   */
   void recharge(double amount);

  /**
   * @brief Takes in an amount, tests whether it can be removed from battery percentage
   * total, then either returns false if it is too much, or returns true
   * @param amount An int which is removed to the total battery percentage
   * @return Returns true if usage removed amount from battery percentage 
   * or false if it failed to do so
   */
   bool usage(double amount);

   int getcurrentCapacity();

  /**
   * @brief Gets the percentage left on the battery
   * @return Returns the current battery percentage
   */
   int getPercentage();
   
   void Update(double dt, std::vector<IEntity*> scheduler);

 private:
   IEntity* component = NULL;
   int currentCapacity;
   const double maxCapacity = 100;
   const double batteryThreshhold = 50;
};

#endif  