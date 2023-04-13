#ifndef DATACOLLECTIONSINGLETON_H_
#define DATACOLLECTIONSINGLETON_H_

#include "IEntity.h"
#include "Drone.h"
#include "Robot.h"
#include <map>

/**
 * @brief This is the data collection class. It is able to accumlate data related
 * to drones and robots in the simulation such as time, distance traveled, account 
 * information, battery usage (Only Drones), and number of trips (Only Drones). It 
 * outputs the CSV file on command.
 */
class DataCollectionSingleton {
 public:
    DataCollectionSingleton();
    ~DataCollectionSingleton();
    void writeTimeInfo(Drone* drone, float time);
    void writeDistanceInfo(Drone* drone, float time);
    void writeAccountInfo(IEntity* entity, double time);
    void writeBatteryUsage(Drone* drone, int time);
    void writeNumberOfTrips(Drone* drone. int time);
    void writeToCSV();

 private:
    DataCollectionSingleton dataCollection = NULL;
    map<Drone*, float> droneTimeInfo;
    map<Robot*, double> robotTimeInfo;
    map<Drone*, float> droneDistanceInfo;
    map<Robot*, float> robotDistanceInfo;
    map<Drone*, double> droneAccountInfo;
    map<Robot*, double> robotAccountInfo;
    map<Drone*, int> batteryUsage;
    map<Drone*, int> numberOfTrips;
};
#endif  // DATACOLLECTIONSINGLETON_H_
