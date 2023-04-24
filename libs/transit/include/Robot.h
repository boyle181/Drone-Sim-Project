#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <chrono>
#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @class Robot
 * @brief Represents a robot in a physical system
 *
 * Robots move using euler integration based on a specified
 * velocity and direction.
 */
class Robot : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the robot's information
   */
  Robot(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Robot() override = default;

  /**
   * @brief Gets the robot's position
   * @return The robot's position
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the robot's direction
   * @return The robot's direction
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the robot's destination
   * @return The robot's destination
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the robot's availability
   * @return The robot's availability
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Gets the robot's details
   * @return The robot's details
   */
  JsonObject GetDetails() const override;

  /**
   * @brief Gets the robot's speed
   * @return The robot's speed
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Get the Strategy Name
   *
   * @return Streategy name
   */
  std::string GetStrategyName() const { return strategyName; }

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  void SetStrategyName(std::string strategyName_) {
    strategyName = strategyName_;
  }

  /**
   * @brief Sets the robot's availability
   * @param choice The new availability of the robot
   */
  void SetAvailability(bool choice);

  /**
   * @brief Sets the robot's position
   * @param pos_ The new position of the robot
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the robot's direction
   * @param dir_ The new direction of the robot
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the robot's destination
   * @param des_ The new destination of the robot
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the robot's totalDistance
   * @param dist_ The new totalDistance of the robot
   */
  void SetDistance(float dist_) { totalDistance = dist_; }

  /**
   * @brief Rotates the robot
   * @param angle The angle by which the robot should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Get the Picked Up status of a robot
   * 
   * @return true, the robot is picked up
   * @return false, the robot is not picked up
   */
  bool GetPickedUp() {return pickedUp; }

  /**
   * @brief Set the Picked Up status of a robot
   * 
   * @param status the status that picked up is set to
   */
  void SetPickedUp(bool status) {pickedUp = status; }
  
  float GetTime(){
    t_end = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration<float, std::milli>(t_end-t_start).count()/1000);
  }

  float GetDistance(){
    return totalDistance;
  }

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;
  std::string strategyName;
  bool pickedUp = false;
  std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
  std::chrono::time_point<std::chrono::high_resolution_clock> t_end;
  float totalDistance = 0;  // For data collection
};

#endif  // ROBOT_H
