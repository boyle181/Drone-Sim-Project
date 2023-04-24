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
  bool GetChargingStatus() { component->GetChargingStatus(); }

  void SetChargingStatus(bool status) { component->SetChargingStatus(status); }

  bool GetAvailability() const { component->GetAvailability(); }

  void SetAvailability(bool choice) { component->SetAvailability(choice); }

  JsonObject GetDetails() const { component->GetDetails(); }

  IEntity* GetEntity() { component->GetEntity(); }

  void Update(double dt, std::vector<IEntity*> scheduler);
   
 private:
   IStrategy* getStrategy();

   IEntity* component;
   double account = 0;
   std::string type;
   bool clientValid = false;                      // Keeps track if a client has been cleared for ride
   const double START_MONEY = 1000.00;
   const int RANGE = 1000;
   const double COST_FOR_TRIP = 20.00;     // Cost per unit of time (trip)
   const double COST_FOR_RECHARGE = 10.00; // Cost per unit of time (recharge)
};

#endif  