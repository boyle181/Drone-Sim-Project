#ifndef RECHARGESTATION_H_
#define RECHARGESTATION_H_

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

// Represents a recharge station in a physical system.

/**
 * @brief Represents a recharge station in a physical system. recharge stations move using euler
 * integration based on a specified velocity and direction.
 */
class RechargeStation : public IEntity {
 public:
  /**
   * @brief RechargeStations are created with a name
   * @param obj JSON object containing the RechargeStation's information
   */
  RechargeStation(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~RechargeStation();

  /**
   * @brief Gets the position of the recharge station
   * @return The position of the recharge station
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the details information of the recharge station
   * @return The details information of the recharge station
   */
  JsonObject GetDetails() const { return details; }

    /**
   * @brief Gets the robot's direction
   * @return The robot's direction
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the recharge stations destination
   * @return The recharge stations destination
   */
  Vector3 GetDestination() const { return position; }


  /**
   * @brief Gets the recharge station's speed
   * @return The recharge station's speed
   */
  float GetSpeed() const { return 0; }

  /**
   * @brief Gets the availability of the recharge station
   * @return The availability of the recharge station
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Sets the position of the recharge station
   * @param pos_ The new position of the recharge station
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the Availability of the recharge station
   * @param choice A bool of whether or not recharge station is available
   */
  void SetAvailability(bool choice) { available = choice; }

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that recharge station cannot be copied.
   */
  RechargeStation(const RechargeStation& rechargeStation) = delete;
  RechargeStation& operator=(const RechargeStation& rechargeStation) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;
};

#endif
