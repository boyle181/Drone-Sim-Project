#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntity.h"
#include "RechargeStation.h"
#include <cstring>
#include <cstdlib>
#include "IEntity.h"
#include "Drone.h"
#include "IStrategy.h"
#include "graph.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include <iostream>


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
   bool hasEnoughBattery(double amount);

  /**
   * @brief Gets the nearest recharge station in the scheduler
   * @param scheduler Vector containing all the entities in the system
   */
   void getNearestRechargeStation(std::vector<IEntity*> scheduler);

  /**
   * @brief Update the wallet decorators 
   * @param dt Type double contain the time since update was last called.
   * @param scheduler Type vectory of IEntity* contains the entities.
   **/
   void Update(double dt, std::vector<IEntity*> scheduler);
  
   /**
   * @brief Gets the amount of battery used by the entity
   * @param entity represents the enttiy that the battery is used for
   */
   double getTripBatteryCost(IEntity* entity);

   /////////////////////////////////////////////////

     /**
   * @brief Gets the position of the entity component.
   * @return The position of the entity component.
   */
  Vector3 GetPosition() const { return component->GetPosition(); }

  /**
   * @brief Gets the destination of the entity component.
   * @return The destination of the entity component.
   */  
  Vector3 GetDestination() const { return component->GetDestination(); }

  /**
   * @brief Gets the direction of the entity component.
   * @return The direction of the entity component.
   */  
  Vector3 GetDirection() const { return component->GetDirection(); }

  /**
   * @brief Gets the speed of the entity component.
   * @return The speed of the entity component.
   */
  float GetSpeed() const { return component->GetSpeed(); }

  /**
   * @brief Set the Picked Up status of a entity
   * 
   * @param status the status that picked up is set to
   */
  bool GetPickedUp() { return component->GetPickedUp(); }

  void SetPickedUp(bool status) { return component->SetPickedUp(status); }

/**
   * @brief Get the Charging Status entity
   * 
   * @return true, entity is at a recharge station charging
   * @return false, entity is not at a recharge station charging
   */
  bool GetChargingStatus() { return component->GetChargingStatus(); }

  void SetChargingStatus(bool status) { component->SetChargingStatus(status); } 

  /**
   * @brief Get the status on wether Entity is going to a 
   * recharge station.
   * 
   * @return true, entity is going a recharge station
   * @return false, entity is not going to a recharge station
   */
  bool GetGoingToRecharge() { return component->GetGoingToRecharge(); }
  
  /**
   * @brief Set the status on wether Entity is going to a 
   * recharge station.
   * 
   * @param status a bool that indicates if the entity is
   *               going to a recharge station
   */
  void SetGoingToRecharge(bool status) { component->SetGoingToRecharge(status); }

  /**
   * @brief Get the Strategy Name
   *
   * @return Streategy name
   */
  std::string GetStrategyName() const { return component->GetStrategyName(); }

  void SetStrategyName(std::string strategyName_) { component->SetStrategyName(strategyName_); }

  /**
   * @brief Sets the robot's position
   * @param pos_ The new position of the robot
   */
  void SetPosition(Vector3 pos_) { component->SetPosition(pos_); }

  /**
   * @brief Sets the robot's direction
   * @param dir_ The new direction of the robot
   */
  void SetDirection(Vector3 dir_) { component->SetDirection(dir_); }
    /**
   * @brief Sets the robot's destination
   * @param des_ The new destination of the robot
   */
  void SetDestination(Vector3 des_) { component->SetDestination(des_); }
   /**
   * @brief Gets the avaliability of the component 
   */
  bool GetAvailability() const { return component->GetAvailability(); }
   /**
   * @brief Sets the avaliability of the component 
   * @param choice represents the new avaliability 
   */
  void SetAvailability(bool choice) { component->SetAvailability(choice); }
  /**
   * @brief Gets the details of the component
   */
  JsonObject GetDetails() const { return component->GetDetails(); }
  /**
   * @brief Gets the entity of the component
   */
  IEntity* GetEntity() { return component->GetEntity(); }
  /**
   * @brief Returns the rotate of the component 
   * @param angle represents the angle of the rotation
   */
  void Rotate(double angle){ component->Rotate(angle); }
  /**
   * @brief Returns the time  of the component 
  */
  float GetTime(){ return component->GetTime(); }
  /**
   * @brief Returns the distance  of the component 
  */
  float GetDistance(){ return component->GetDistance(); }
   
  int GetId() const { return component->GetId(); }
  
 private:
   IStrategy* getStrategy(IEntity* entity);
   IEntity* component = NULL;
   IEntity* nearestRechargeStation = NULL;
   IStrategy* toRechargeStation = NULL;
   double currentCapacity;
   const double maxCapacity = 3000;
   const double BATTERY_MULTIPLIER = .35;
   const double RECHARGE_RATE = 1;
   bool clientValid = false;
   bool canUpdateBattery = false;
   bool writeCSV = false;
};

#endif  