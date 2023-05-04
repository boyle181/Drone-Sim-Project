#ifndef WALLET_DECORATOR_H_
#define WaLLET_DECORATOR_H_
#include "IEntity.h"
#include "Robot.h"
#include "Drone.h"
#include "IStrategy.h"
#include "graph.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include <iostream>
#include <cstring>
#include <cstdlib>



/**
 * @brief this class inherits from the IStrategy class. It is used 
 * to create changeable and trackable wallets inside drones and robots.
 */
class WalletDecorator : public IEntity {

 public:

  /**
   * @brief Wallet is created with a random preset total money value
   * @param entity a pointer IEntity object in which the wallet is created
   */
  WalletDecorator(IEntity* entity);

  /**
   * @brief WalletDecorator Destructor
   */
  ~WalletDecorator(){ delete component; }

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
  /**
   * @brief Update the wallet decorators 
   * @param dt Type double contain the time since update was last called.
   * @param scheduler Type vectory of IEntity* contains the entities.
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);
   
  int GetId() const { return component->GetId(); }

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


 private:
   IStrategy* getStrategy(IEntity* entity);
   double getCostForTrip(IEntity* entity);
   IEntity* component;
   double account = 0;
   std::string type;
   bool clientValid = false;                      // Keeps track if a client has been cleared for ride
   const double START_MONEY = 1000.00;
   const int RANGE = 1000;
   const double TRIP_MULTIPLIER = 10.0;     // Cost per unit of time (trip)
   const double COST_FOR_RECHARGE = 10.00; // Cost per unit of time (recharge)
   Vector3 pickUpDestination;
   Vector3 finalDestination;
   bool transactionComplete = false;
};

#endif  