// Copyright 2023 Jason Paciorek, Aidan Boyle, Rebecca Hoff, Nuh Misirli

#include "DataCollectionSingleton.h"

#include <ctime>
#include <filesystem>
#include <iostream>

DataCollectionSingleton::DataCollectionSingleton() {
  // *** Creates CSV file if it is not present ***
  auto csvDirectory = std::filesystem::create_directory("CSV");

  // *** Get Current time and adjusts file name accordingly ***
  time_t timer;
  struct tm* timeinfo;
  time(&timer);
  timeinfo = localtime(&timer);
  char name[100];
  strftime(name, 100, "CSV/simData %H:%M:%S.csv", timeinfo);
  filename = name;
}

DataCollectionSingleton* DataCollectionSingleton::getInstance() {
  if (dataCollection == NULL) {
    dataCollection = new DataCollectionSingleton();
  }
  return dataCollection;
}

void DataCollectionSingleton::writeTimeInfo(int ID, float time) {
  timeInfo[ID] = time;
}

void DataCollectionSingleton::writeDistanceInfo(int ID, float distance) {
  distanceInfo[ID] = distance;
}

void DataCollectionSingleton::writeAccountInfo(int ID, double accountBalance) {
  accountInfo[ID] = accountBalance;
}

void DataCollectionSingleton::writeBatteryUsage(int ID, double usage) {
  batteryUsage[ID] = usage;
}

void DataCollectionSingleton::writeNumberOfTrips(int ID, int trips) {
  numberOfTrips[ID] = trips;
}

void DataCollectionSingleton::ClearMaps() {
  timeInfo.clear();
  distanceInfo.clear();
  accountInfo.clear();
  batteryUsage.clear();
  numberOfTrips.clear();
}

void DataCollectionSingleton::writeToCSV() {
  // *** Open csv file ***
  std::ofstream data;
  data.open(filename, std::ios::trunc);

  // *** Top Axis ***
  data << "ID, Time, Distance, Account($), Battery Usage, Number of Trips\n";

  // *** Gets data for all Drones and enters it into a .csv file ***
  for (std::map<int, float>::iterator entry = timeInfo.begin();
       entry != timeInfo.end(); ++entry) {
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
    if (ID == 0) {  // NoteToSelf: This will break when there's multiple drones
      data << std::to_string(batteryUsage[ID]);
      data << ", ";
      data << std::to_string(numberOfTrips[ID]);
    } else {
      data << "N/A, N/A";
    }
    data << "\n";
  }
  data.close();
}
