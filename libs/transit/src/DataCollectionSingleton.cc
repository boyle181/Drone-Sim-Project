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
    char name[100];
    sprintf(name, "simData-%s.csv", std::ctime(&end_time));
    // *** Open csv file ***
    std::ofstream data;
    data.open (name, std::ios::trunc);
    std::string row = ""; // Acc for writing a row to .csv

    // *** Top Axis ***
    data << "ID, Time, Distance, Account($), Battery Usage, Number of Trips\n";

    // *** Gets data for all Drones and enters it into a .csv file ***
    for (std::map<int, float>::iterator entry = timeInfo.begin(); entry != timeInfo.end(); ++entry){
        int ID = entry->first;
        // *** Information all entities have ***
        row.append(std::to_string(entry->first));
        row.append(", ");
        row.append(std::to_string(timeInfo[ID]));
        row.append(", ");
        row.append(std::to_string(distanceInfo[ID]));
        row.append(", ");
        row.append(std::to_string(accountInfo[ID]));
        row.append(", ");

        // // *** Information only for battery wrapped entities ***
        // if (batteryUsage.find(ID) != batteryUsage.end()){
        //     row.append(std::to_string(batteryUsage[ID]));
        // }
        // else {
        //     row.append("N/A");
        // }
        // row.append(", ");

        // // *** Information only for wallet wrapped entities ***
        // if (numberOfTrips.find(ID) != numberOfTrips.end()){
        //     row.append(std::to_string(numberOfTrips[ID]));
        // }
        // else {
        //     row.append("N/A");
        // }

        if (ID == 0){
            row.append(std::to_string(batteryUsage[ID]));
            row.append(", ");
            row.append(std::to_string(numberOfTrips[ID]));
        }
        else{
            row.append("N/A, N/A");
        }
        
        row.append("\n");
        data << row;
    }
    ClearMaps();
    data.close();
}
