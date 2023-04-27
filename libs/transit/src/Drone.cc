#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "WalletDecorator.h"
#include "DataCollectionSingleton.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
  t_start = std::chrono::high_resolution_clock::now();
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
}



void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {

  // maybe have to fix if drones try to pik up recharge stations
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }
      

  if (nearestEntity) {
      std::cout << "nearest entity\n";

    // Set required variables
    std::string strategyName = nearestEntity->GetStrategyName();
    IStrategy* strategy;
    std::vector<float> path;
    
    // set availability to the nearest entity
    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;

    // Set destinations
    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination();

    // Wrap Beeline strat and calculate its distance.
    toRobot = new BeelineStrategy(position, destination);
    beelineTripDistance = toRobot->getTotalDistance();


    // Wrap Celebration decorators and path strategies
    if (strategyName == "astar") {
      strategy = new AstarStrategy(destination, finalDestination, graph);
      toFinalDestination =
        new JumpDecorator(strategy);
    } else if (strategyName == "dfs") {
      strategy = new DfsStrategy(destination, finalDestination, graph);
      toFinalDestination =
        new SpinDecorator(new JumpDecorator(strategy));
    } else if (strategyName == "dijkstra") {
      toFinalDestination =
        new JumpDecorator(new SpinDecorator(new DijkstraStrategy(destination, finalDestination, graph)));
    } else {
        toFinalDestination = new BeelineStrategy(destination, finalDestination);
    }
    pathTripDistance = strategy->getTotalDistance();
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  // gdb -tui  ./build/bin/transit_service
  // set args 8081 apps/transit_service/web
  // run
  // http://127.0.0.1:8081/
  // ./build/bin/transit_service 8081 apps/transit_service/web/


  DataCollectionSingleton* dataCollection = DataCollectionSingleton::getInstance();

  if (available) {
    GetNearestEntity(scheduler);
  }

  if (toRobot) {
    toRobot->Move(this, dt);

    if (toRobot->IsCompleted()) {
      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
    }
  } 
  else if (toFinalDestination) {
    toFinalDestination->Move(this, dt);

    if (nearestEntity && pickedUp) {
      nearestEntity->SetPickedUp(true);
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      totalDistance = totalDistance + pathTripDistance + beelineTripDistance;
      totalTrips++;

      // Drone data collection info
      dataCollection->writeBatteryUsage(this, 0);
      dataCollection->writeTimeInfo(this, this->GetTime());
      dataCollection->writeDistanceInfo(this, totalDistance);
      dataCollection->writeNumberOfTrips(this, totalTrips);

      // Robots data collection info
      dataCollection->writeTimeInfo(nearestEntity, nearestEntity->GetTime());
      dataCollection->writeDistanceInfo(nearestEntity, pathTripDistance);
      std::cout << "path distance:" << pathTripDistance << std::endl;
      std::cout << "beeline distance:" << beelineTripDistance << std::endl;

      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      pickedUp = false;
      std::cout << "\ndataCollected" << std::endl;
      dataCollection->writeToCSV();
    }
  }
}


void Drone::SetAvailability(bool choice) { available = choice; }

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}
