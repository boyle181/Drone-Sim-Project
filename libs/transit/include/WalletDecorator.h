#ifndef LIBS_TRANSIT_INCLUDE_WALLETDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_WALLETDECORATOR_H_

// Copyright 2023 Jason Paciorek, Aidan Boyle, Rebecca Hoff, Nuh Misirli

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "../../routing/include/graph.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "Drone.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "Robot.h"

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
  explicit WalletDecorator(IEntity* entity);

  /**
   * @brief WalletDecorator Destructor
   */
  ~WalletDecorator() { delete component; }

  /**
   * @brief Gets the position of the component.
   * @return The position of the component.
   */
  Vector3 GetPosition() const { return component->GetPosition(); }

  /**
   * @brief Gets the destination of the component.
   * @return The destination of the component.
   */
  Vector3 GetDestination() const { return component->GetDestination(); }

  /**
   * @brief Gets the direction of the component.
   * @return The direction of the component.
   */
  Vector3 GetDirection() const { return component->GetDirection(); }

  /**
   * @brief Gets the speed of the component.
   * @return The speed of the component.
   */
  float GetSpeed() const { return component->GetSpeed(); }

  /**
   * @brief Set the Picked Up status of a component
   *
   * @param status the status that picked up is set to
   */
  bool GetPickedUp() { return component->GetPickedUp(); }

  /**
   * @brief Set the Picked Up status of the component
   *
   * @param status the status that picked up is set to
   */
  void SetPickedUp(bool status) { return component->SetPickedUp(status); }

  /**
   * @brief Get the Charging Status of the component
   *
   * @return true, component is at a recharge station charging
   * @return false, component is not at a recharge station charging
   */
  bool GetChargingStatus() { return component->GetChargingStatus(); }

  /**
   * @brief Set the Recharging Status of the component
   *
   * @param status a bool that indicates if the component is
   *               recharging at a recharge station
   */
  void SetChargingStatus(bool status) { component->SetChargingStatus(status); }

  /**
   * @brief Get the name of the strategy as a string
   *
   * @return Streategy name
   */
  std::string GetStrategyName() const { return component->GetStrategyName(); }

  /**
   * @brief Set the Strategy Name as a string
   *
   * @param strategyName_ Strategy name
   */
  void SetStrategyName(std::string strategyName_) {
    component->SetStrategyName(strategyName_);
  }

  /**
   * @brief Sets the component's position
   * @param pos_ The new position of the component
   */
  void SetPosition(Vector3 pos_) { component->SetPosition(pos_); }

  /**
   * @brief Sets the component's direction
   * @param dir_ The new direction of the component
   */
  void SetDirection(Vector3 dir_) { component->SetDirection(dir_); }

  /**
   * @brief Sets the component's destination
   * @param des_ The new destination of the component
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
   * @brief Gets the entity connected to the component
   */
  IEntity* GetEntity() { return component->GetEntity(); }

  /**
   * @brief rotate's component
   * @param angle represents the angle of the rotation
   */
  void Rotate(double angle) { component->Rotate(angle); }

  /**
   * @brief Returns the time of the component
   */
  float GetTime() { return component->GetTime(); }

  /**
   * @brief Returns the distance of the component
   */
  float GetDistance() { return component->GetDistance(); }

  /**
   * @brief Updates the wallet decorators
   * @param dt Type double contain the time since update was last called.
   * @param scheduler Type vectory of IEntity* contains the entities.
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Gets the ID of the component entity.
   * @return The ID of the component entity.
   */
  int GetId() const { return component->GetId(); }

  /**
   * @brief Get the status on whether component is going to a
   * recharge station.
   *
   * @return true, component is going a recharge station
   * @return false, component is not going to a recharge station
   */
  bool GetGoingToRecharge() { return component->GetGoingToRecharge(); }

  /**
   * @brief Set the status on whether component is going to a
   * recharge station.
   *
   * @param status a bool that indicates if the component is
   *               going to a recharge station
   */
  void SetGoingToRecharge(bool status) {
    component->SetGoingToRecharge(status);
  }

 private:
  IStrategy* getStrategy(IEntity* entity);
  double getCostForTrip(IEntity* entity);
  IEntity* component;
  double account = 0;
  std::string type;
  bool clientValid =
      false;  // Keeps track if a client has been cleared for ride
  const double START_MONEY = 1000.00;
  const int RANGE = 1000;
  const double TRIP_MULTIPLIER = 10.0;     // Cost per unit of time (trip)
  const double COST_FOR_RECHARGE = 10.00;  // Cost per unit of time (recharge)
  Vector3 pickUpDestination;
  Vector3 finalDestination;
  bool transactionComplete = false;
};

#endif  // LIBS_TRANSIT_INCLUDE_WALLETDECORATOR_H_
