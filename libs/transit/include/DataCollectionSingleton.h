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
    void writeTimeInfo(int ID, float time);

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
    void writeDistanceInfo(int ID, float distance);

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
    void writeAccountInfo(int ID, double accountBalance);

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
    void writeBatteryUsage(int ID, double usage);

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
    void writeNumberOfTrips(int ID, int trips);

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
    DataCollectionSingleton();
    void ClearMaps();
    std::string filename;
    std::map<int, float> timeInfo;
    std::map<int, float> distanceInfo;
    std::map<int, double> accountInfo;
    std::map<int, double> batteryUsage;
    std::map<int, int> numberOfTrips;
};

// Our Static instance of the DataCollectionSingleton
static DataCollectionSingleton* dataCollection = NULL;

#endif  // DATACOLLECTIONSINGLETON_H_
