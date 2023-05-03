#include <cstdio>
#include <iostream>
#include <chrono>
#include <ctime>  
#include "DataCollectionSingleton.h"

DataCollectionSingleton* DataCollectionSingleton::getInstance(){
    if (dataCollection == NULL){
        dataCollection = new DataCollectionSingleton();
    }
    return dataCollection;
}

void DataCollectionSingleton::writeTimeInfo(int ID, float time){
    timeInfo[ID] = time;
}

void DataCollectionSingleton::writeDistanceInfo(int ID, float distance){
    distanceInfo[ID] = distance;
}

void DataCollectionSingleton::writeAccountInfo(int ID, double accountBalance){
    accountInfo[ID] = accountBalance;
}

void DataCollectionSingleton::writeBatteryUsage(int ID, double usage){
    batteryUsage[ID] = usage;
}

void DataCollectionSingleton::writeNumberOfTrips(int ID, int trips){
    numberOfTrips[ID] = trips;
}

void DataCollectionSingleton::ClearMaps() {
    timeInfo.clear();
    distanceInfo.clear();
    accountInfo.clear();
    batteryUsage.clear();
    numberOfTrips.clear();
}

void DataCollectionSingleton::writeToCSV(){
    
    // *** Get Time for naming CSV ***
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::string name = "CSV/simData-";
    name.append(std::ctime(&end_time));
    name.append(".csv");

    // *** Open csv file ***
    std::ofstream data;
    data.open(name, std::ios::trunc);

    // *** Top Axis ***
    data << "ID, Time, Distance, Account($), Battery Usage, Number of Trips\n";

    // *** Gets data for all Drones and enters it into a .csv file ***
    for (std::map<int, float>::iterator entry = timeInfo.begin(); entry != timeInfo.end(); ++entry){
        int ID = entry->first;

        // *** Information all entities have ***
        data << std::to_string(entry->first);
        data << ", ";
        data << std::to_string(timeInfo[ID]);
        data << ", ";
        data << std::to_string(distanceInfo[ID]);
        data << ", ";
        data << std::to_string(accountInfo[ID]);
        data << ", ";

        // *** Information only for drone ***
        if (ID == 0){ // Note: This will break when multiple drone enter sim
            data << std::to_string(batteryUsage[ID]);
            data << ", ";
            data << std::to_string(numberOfTrips[ID]);
        }
        else{
            data << "N/A, N/A";
        }

        data << "\n";
    }
    ClearMaps();
    data.close();
}
