#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the speed of the drone
   * @return The speed of the drone
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the drone
   * @return The position of the drone
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the drone
   * @return The direction of the drone
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the drone
   * @return The destination of the drone
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Gets the availability of the drone
   * @return The availability of the drone
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Gets the nearest entity in the scheduler
   * @param scheduler Vector containing all the entities in the system
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the drone
   * @param pos_ The new position of the drone
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the drone
   * @param dir_ The new direction of the drone
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the robot's availability
   * @param choice The new availability of the robot
   */
  void SetAvailability(bool choice);

  /**
   * @brief Sets the destination of the drone
   * @param des_ The new destination of the drone
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Makes the drone jump
   * @param height The height at which the drone should jump
   */
  void Jump(double height);

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Get the To Final Destination strategy
   * 
   * @return IStrategy* the final destination strategy.
   *         this is the strategy used after pick up
   */
  IStrategy* GetToFinalDestination() { return toFinalDestination; }
  
  /**
   * @brief Get the Charging Status object
   * 
   * @return true, Drone is at a recharge station charging
   * @return false, Drone is not at a recharge station charging
   */
  bool GetChargingStatus() { return rechargeStatus; }
  
  /**
   * @brief Set the Recharging Status of the drone
   * 
   * @param status a bool that indicates if the drone is
   *               recharging at a recharge station
   */
  void SetChargingStatus(bool status) { rechargeStatus = status; }
  
  /**
   * @brief Get the nearest entity that the drone is pursuing
   * 
   * @return IEntity* the entity the drone is pursuing
   */
  IEntity* GetEntity() {return nearestEntity; }

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  std::string color = "None";  // None means default color
  float jumpHeight = 0;
  bool goUp = true;  // jump helper
  Vector3 destination;
  float speed;
  bool available;
  bool pickedUp;
  IEntity* nearestEntity = nullptr;
  IStrategy* toRobot = nullptr;
  IStrategy* toFinalDestination = nullptr;
  float pathTripDistance = 0;
  float beelineTripDistance = 0;
  float tripMoneyCost = 0; // only going to charge robot for when it gets picked up and dropped to final dest
  bool rechargeStatus = false;
};

#endif
