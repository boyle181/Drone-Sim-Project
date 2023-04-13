#ifndef RECHARGESTATION_H_
#define RECHARGESTATION_H_

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"

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
   * @brief Removing the copy constructor and assignment operator
   * so that recharge station cannot be copied.
   */
  RechargeStation(const RechargeStation& rechargeStation) = delete;
  RechargeStation& operator=(const RechargeStation& rechargeStation) = delete;

 private:
  JsonObject details;
  Vector3 position;
  bool available;
};

#endif
