#ifndef LIBS_TRANSIT_INCLUDE_BATTERYDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_BATTERYDECORATOR_H_

// Copyright 2023 Jason Paciorek, Aidan Boyle, Rebecca Hoff, Nuh Misirli

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "../../routing/include/graph.h"
#include "./IStrategy.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "Drone.h"
#include "IEntity.h"
#include "RechargeStation.h"

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
  explicit BatteryDecorator(IEntity* entity);

  /**
   * @brief Takes in an amount, tests whether it can be removed from battery
   * percentage total, then either returns false if it is too much, or returns
   * true
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
   * @brief Gets the amount of battery used by entity over the course of
   * a trip.
   * @param entity the entity that will be calculated for battery
   * usage over the course of a trip
   */
  double getTripBatteryCost(IEntity* entity);

  /////////////////////////////////////////////////

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
   * @brief Get the Picked Up status of the component
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
   * @return true, the entity component is at a recharge station charging
   * @return false, the entity component is not at a recharge station charging
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
   * @brief Get the status on wether the component is going to a
   * recharge station.
   *
   * @return true, the component is going a recharge station
   * @return false, the component is not going to a recharge station
   */
  bool GetGoingToRecharge() { return component->GetGoingToRecharge(); }

  /**
   * @brief Set the status on wether the component is going to a
   * recharge station.
   *
   * @param status a bool that indicates if the component is
   *               going to a recharge station
   */
  void SetGoingToRecharge(bool status) {
    component->SetGoingToRecharge(status);
  }

  /**
   * @brief Get the Strategy Name of the component
   *
   * @return The Strategy name
   */
  std::string GetStrategyName() const { return component->GetStrategyName(); }

  /**
   * @brief Set the Strategy Name of the component
   *
   * @param strategyName_ Strategy name
   */
  void SetStrategyName(std::string strategyName_) {
    component->SetStrategyName(strategyName_);
  }

  /**
   * @brief Sets the component position
   * @param pos_ The new position of the component
   */
  void SetPosition(Vector3 pos_) { component->SetPosition(pos_); }

  /**
   * @brief Sets the component direction
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
   * @brief Gets the entity of the component
   */
  IEntity* GetEntity() { return component->GetEntity(); }

  /**
   * @brief Returns the rotate of the component
   * @param angle represents the angle of the rotation
   */
  void Rotate(double angle) { component->Rotate(angle); }

  /**
   * @brief Returns the time of the component since it's
   * creation.
   */
  float GetTime() { return component->GetTime(); }

  /**
   * @brief Returns the distance of the component
   */
  float GetDistance() { return component->GetDistance(); }

  /**
   * @brief Gets the ID of the component.
   * @return The ID of the the component.
   */
  int GetId() const { return component->GetId(); }

 private:
  IStrategy* getStrategy(IEntity* entity);
  IEntity* component = NULL;
  IEntity* nearestRechargeStation = NULL;
  IStrategy* toRechargeStation = NULL;
  double currentCapacity;
  const double maxCapacity = 2000;
  const double BATTERY_MULTIPLIER = .35;
  const double RECHARGE_RATE = 100;
  bool clientValid = false;
  bool canUpdateBattery = false;
  bool writeCSV = false;
  double totalTripBatteryUsage = 0;
};

#endif  // LIBS_TRANSIT_INCLUDE_BATTERYDECORATOR_H_
