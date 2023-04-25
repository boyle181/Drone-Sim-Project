
#include "DataCollectionSingleton.h"

DataCollectionSingleton* DataCollectionSingleton::getInstance(){
    if (dataCollection == NULL){
        dataCollection = new DataCollectionSingleton();
    }
    return dataCollection;
}

void DataCollectionSingleton::writeTimeInfo(IEntity* entity, float time){
    timeInfo[entity] = time;
}

void DataCollectionSingleton::writeDistanceInfo(IEntity* entity, float distance){
    distanceInfo[entity] = distance;
}

void DataCollectionSingleton::writeAccountInfo(IEntity* entity, double accountBalance){
    accountInfo[entity] = accountBalance;
}

void DataCollectionSingleton::writeBatteryUsage(IEntity* entity, int usage){
    batteryUsage[entity] = usage;
}

void DataCollectionSingleton::writeNumberOfTrips(IEntity* entity, int trips){
    numberOfTrips[entity] = trips;
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
    for (std::map<IEntity*, float>::iterator entry = timeInfo.begin(); entry != timeInfo.end(); ++entry){
        IEntity* entity = entry->first;
        std::string type = entity->GetDetails()["type"].ToString(); 
        row.append(std::to_string(entity->GetId()));
        row.append(", ");
        row.append(std::to_string(timeInfo[entity]));
        row.append(", ");
        row.append(std::to_string(distanceInfo[entity]));
        row.append(", ");
        row.append(std::to_string(accountInfo[entity]));
        row.append(", ");
        if (type.compare("drone") == 0){
            row.append(std::to_string(batteryUsage[entity]));
            row.append(", ");
            row.append(std::to_string(numberOfTrips[entity]));
        }
        else{
            row.append(" N/A, N/A");
        }
        row.append("\n");
        data << row;
        count++;
    }
    data.close();
}
