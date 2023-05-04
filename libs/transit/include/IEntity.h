#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"
using namespace routing;

/**
 * @class IEntity 
 * @brief Represents an entity in a physical system.
 *
 * An IEntity object has a unique ID, a position, a direction, a destination,
 * and details. It also has a speed, which determines how fast the entity moves
 * in the physical system. Subclasses of IEntity can override the `Update`
 * function to implement their own movement behavior.
 */
class IEntity {
 public:
  /**
   * @brief Constructor that assigns a unique ID to the entity.
   */
  IEntity() {
    static int currentId = 0;
    id = currentId;
    currentId++;
  }

  /**
   * @brief Virtual destructor for IEntity.
   */
  virtual ~IEntity() { delete graph; }

  /**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  virtual int GetId() const { return id; }

  /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  virtual Vector3 GetPosition() const = 0;

  /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  virtual Vector3 GetDirection() const = 0;

  /**
   * @brief Gets the destination of the entity.
   * @return The destination of the entity.
   */
  virtual Vector3 GetDestination() const = 0;

  /**
   * @brief Gets the details of the entity.
   * @return The details of the entity.
   */
  virtual JsonObject GetDetails() const = 0;

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  virtual std::string GetColor() const { return "None"; }

  /**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  virtual float GetSpeed() const = 0;

  /**
   * @brief Gets the availability of the entity.
   * @return The availability of the entity.
   */
  virtual bool GetAvailability() const {}

  /**
   * @brief Get the Strategy Name
   *
   * @return Streategy name
   */
  virtual std::string GetStrategyName() const {}

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  virtual void SetStrategyName(std::string strategyName_) {}

  /**
   * @brief Sets the availability of the entity.
   * @param choice The desired availability of the entity.
   */
  virtual void SetAvailability(bool choice) {}

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   * @param scheduler The list of all entities in the system.
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler) {}

  /**
   * @brief Sets the graph object used by the entity in the simulation.
   * @param graph The IGraph object to be used.
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  virtual void SetPosition(Vector3 pos_) {}

  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  virtual void SetDirection(Vector3 dir_) {}

  /**
   *@brief Set the destination of the entity.
   *@param des_ The new destination of the entity.
   */
  virtual void SetDestination(Vector3 des_) {}

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  virtual void SetColor(std::string col_) {}

  /**
   * @brief Rotate the entity.
   * @param angle The angle to rotate the entity by.
   */
  virtual void Rotate(double angle) {}

  /**
   * @brief Make the entity jump.
   * @param height The height to make the entity jump.
   */
  virtual void Jump(double height) {}
  
  /**
   * @brief Sets nearest entity in the scheduler
   */
  void SetEntity(IEntity* entity) { }

  virtual float Random(float Min, float Max) {
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
  }

  // ************* I added everything from here below **********

    /**
   * @brief Get the Picked Up status of a entity
   * 
   * @return true, the entity is picked up
   * @return false, the entity is not picked up
   */
  virtual bool GetPickedUp() {}

  /**
   * @brief Set the Picked Up status of a entity
   * 
   * @param status the status that picked up is set to
   */
  virtual void SetPickedUp(bool status) {}
  
  /**
   * @brief Get the Charging Status entity
   * 
   * @return true, entity is at a recharge station charging
   * @return false, entity is not at a recharge station charging
   */
  virtual bool GetChargingStatus() {}
  
  /**
   * @brief Set the Recharging Status of the entity
   * 
   * @param status a bool that indicates if the entity is
   *               recharging at a recharge station
   */
  virtual void SetChargingStatus(bool status) {}
  
  /**
   * @brief Get the status on wether Entity is going to a 
   * recharge station.
   * 
   * @return true, entity is going a recharge station
   * @return false, entity is not going to a recharge station
   */
  virtual bool GetGoingToRecharge() {}
  
  /**
   * @brief Set the status on wether Entity is going to a 
   * recharge station.
   * 
   * @param status a bool that indicates if the entity is
   *               going to a recharge station
   */
  virtual void SetGoingToRecharge(bool status) {}

  /**
   * @brief Get the nearest entity that the entity is pursuing
   * 
   * @return IEntity* the entity the entity (this entity) is pursuing
   */
  virtual IEntity* GetEntity(){};

  virtual float GetTime(){};
  virtual float GetDistance(){};
  virtual void SetDistance(float dist_){};
  virtual const IGraph* getGraph() const {return graph; }

 protected:
  int id;
  const IGraph* graph;
};

#endif
