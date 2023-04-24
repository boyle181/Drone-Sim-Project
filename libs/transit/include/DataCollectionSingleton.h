#ifndef DATACOLLECTIONSINGLETON_H_
#define DATACOLLECTIONSINGLETON_H_

#include "IEntity.h"
#include "Drone.h"
#include "Robot.h"
#include <map>
#include <fstream>

/**
 * @brief This is the data collection class. It is able to accumlate data related
 * to drones and robots in the simulation such as time, distance traveled, account 
 * information, battery usage (Only Drones), and number of trips (Only Drones). It 
 * outputs the CSV file on command.
 */
class DataCollectionSingleton {
 public:

   /**
    * @brief Get the Instance object
    * 
    * @return DataCollectionSingleton* 
    */
    static DataCollectionSingleton* getInstance();

    /**
     * @brief Takes an entity pointer that will be associated
     * with the provided time. Only a single value can be assoicated
     * with a pointer. Previous values will be overwritten.
     * 
     * @param entity A pointer to the entity that is assoicated
     * with the time provided.
     * @param time A float representing the time data that is 
     * assoicated with entity pointer
     */
    void writeTimeInfo(IEntity* entity, float time);

    /**
     * @brief Takes an entity pointer that will be associated
     * with the provided distance. Only a single value can be 
     * assoicated with a pointer. Previous values will be overwritten.
     * 
     * @param entity A pointer to the entity that is assoicated
     * with the distance provided.
     * @param distance A float representing the distanced that is 
     * assoicated with entity pointer
     */
    void writeDistanceInfo(IEntity* entity, float distance);

    /**
     * @brief Takes an entity pointer that will be associated
     * with the provided account balance. Only a single value 
     * can be assoicated with a pointer. Previous values will 
     * be overwritten.
     * 
     * @param entity A pointer to the entity that is assoicated
     * with the account balance provided.
     * @param account A double representing the account balance
     * that is assoicated with entity pointer
     */
    void writeAccountInfo(IEntity* entity, double accountBalance);

    /**
     * @brief Takes an drone pointer that will be associated
     * with the provided battery usage. Only a single value 
     * can be assoicated with a pointer. Previous values will 
     * be overwritten.
     * 
     * @param drone A pointer to the drone that is assoicated
     * with the battery usage provided.
     * @param batteryUsage An int representing the battery usage
     * that is assoicated with drone pointer
     */
    void writeBatteryUsage(IEntity* entity, int usage);

    /**
     * @brief Takes an drone pointer that will be associated
     * with the provided number of trips. Only a single value 
     * can be assoicated with a pointer. Previous values will 
     * be overwritten.
     * 
     * @param drone A pointer to the drone that is assoicated
     * with the number of trips provided.
     * @param trips An int representing the number of trips
     * that is assoicated with drone pointer
     */
    void writeNumberOfTrips(IEntity* entity, int trips);

    /**
     * @brief Outputs all data that has been collected to a csv file.
     * The file's name will be: "simData.csv". 
     */
    void writeToCSV();

    /**
     * Singletons are not cloneable and assignable.
     */
    DataCollectionSingleton(DataCollectionSingleton &other) = delete;
    void operator=(const DataCollectionSingleton &) = delete;

 private:
    DataCollectionSingleton() { }
    std::map<IEntity*, float> timeInfo;
    std::map<IEntity*, float> distanceInfo;
    std::map<IEntity*, double> accountInfo;
    std::map<IEntity*, int> batteryUsage;
    std::map<IEntity*, int> numberOfTrips;
};

// Our Static instance of a the DataCollectionSingleton
static DataCollectionSingleton* dataCollection = NULL;

#endif  // DATACOLLECTIONSINGLETON_H_
