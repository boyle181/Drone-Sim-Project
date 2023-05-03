
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

void DataCollectionSingleton::printBatteryInfo(){
    for (std::map<int, double>::iterator entry = batteryUsage.begin(); entry != batteryUsage.end(); ++entry){
        std::cout <<  entry->first << ": " << entry->second << std::endl;
    }
    std::cout << std::endl;
}

double DataCollectionSingleton::getBattery(int ID){
    return batteryUsage[ID];
}

void DataCollectionSingleton::writeToCSV(){
    
    // *** Open csv file ***
    std::ofstream data;
    data.open ("simData101.csv", std::ios::trunc);
    std::string row = ""; // Acc for writing a row to .csv

    // *** Top Axis ***
    data << "ID, Time, Distance, Account($), Battery Usage, Number of Trips\n";

    // *** Gets data for all Drones and enters it into a .csv file ***
    int count = 1;
    for (std::map<int, float>::iterator entry = timeInfo.begin(); entry != timeInfo.end(); ++entry){
        std::cout <<  entry->first << ": " << entry->second << std::endl;
        int ID = entry->first;
        row.append(std::to_string(entry->first));
        row.append(", ");
        row.append(std::to_string(timeInfo[ID]));
        row.append(", ");
        row.append(std::to_string(distanceInfo[ID]));
        row.append(", ");
        row.append(std::to_string(accountInfo[ID]));
        row.append(", ");
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
        count++;
    }
    data.close();
}
