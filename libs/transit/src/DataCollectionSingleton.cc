
#include "DataCollectionSingleton.h"

DataCollectionSingleton::DataCollectionSingleton(){
    if (dataCollection == NULL){
        dataCollection = new DataCollectionSingleton(value);
    }
    return dataCollection;
}

DataCollectionSingleton::~DataCollectionSingleton(){
    if (dataCollection != NULL){
        delete dataCollection;
    }
}

void DataCollectionSingleton::writeTimeInfo(IEntity* entity, float time){
    std::string type = (entity->GetDetails())["type"];
    if (type.compare("drone") == 0) {
        droneTimeInfo[entity] = time;
        return;
    }
    robotTimeInfo[entity] = time;
}

void DataCollectionSingleton::writeDistanceInfo(IEntity* entity, float distance){
    std::string type = (entity->GetDetails())["type"];
    if (type.compare("drone") == 0) {
        droneDistanceInfo[entity] = distance;
        return;
    }
    robotDistanceInfo[entity] = distance;
}

void DataCollectionSingleton::writeAccountInfo(IEntity* entity, double account){
    std::string type = (entity->GetDetails())["type"];
    if (type.compare("drone") == 0) {
        droneAccountInfo[entity] = account;
        return;
    }
    robotAccountInfo[entity] = account;
}

void DataCollectionSingleton::writeBatteryUsage(Drone* drone, int usage){
    batteryUsage[drone] = usage;
}

void DataCollectionSingleton::writeNumberOfTrips(Drone* drone. int trips){
    numberOfTrips[drone] = trips;
}

void DataCollectionSingleton::writeToCSV(){
    
    // *** Open csv file ***
    std::ofstream data;
    data.open ("simData.csv");
    std::string row = ""; // Acc for writing a row to .csv

    // *** Top Axis ***
    data << "Name, Time, Distance, Account($), Battery Usage, Number of Trips";

    // *** Gets data for all Drones and enters it into a .csv file ***
    int count = 1;
    for (std::map<Drone*, float>::iterator entry = droneTimeInfo.begin(); entry != droneTimeInfo.end(); ++entry){
        Drone* drone = entry->first;
        row += "Drone #" + std::to_string(count);
        row += ",";
        row += droneTimeInfo[drone];
        row += ",";
        row += droneDistanceInfo[drone];
        row += ",";
        row += droneAccountInfo[drone];
        row += ",";
        row += batteryUsage[drone];
        row += ",";
        row += numberOfTrips[drone];
        row += "\n";
        data << row;
        count++;
    }

    // *** Gets data for all Robots and enters it into a .csv file ***
    // ***       And it fills in the last 2 columns with N/A       ***
    count = 1;
    for (std::map<Robot*, float>::iterator entry = robotTimeInfo.begin(); entry != robotTimeInfo.end(); ++entry){
        Robot* robot = entry->first;
        row += "Robot #" + std::to_string(count);
        row += ",";
        row += robotTimeInfo[robot];
        row += ",";
        row += robotDistanceInfo[robot];
        row += ",";
        row += robotAccountInfo[robot];
        row += "N/A,N/A";
        row += "\n";
        data << row;
        count++;
    }
    data.close();
}
