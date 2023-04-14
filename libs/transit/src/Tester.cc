#include "DataCollectionSingleton.h"
#include "IEntity.h"

// g++ -g Tester.cc -o tester -I ../include -I ../../routing/include -I ../../../dependencies/include
// valgrind --leak-check=full ./tester

int main(){
    DataCollectionSingleton* single = DataCollectionSingleton::getInstance();

    JsonObject details;
    details["position"];
    details["direction"];
    details["speed"];

    Drone* d1 = new Drone(details);
    Robot* r1 = new Robot(details);
    Drone* d2 = new Drone(details);
    Robot* r2 = new Robot(details);
    Drone* d3 = new Drone(details);
    Robot* r3 = new Robot(details);

    single->DataCollectionSingleton::writeTimeInfo(d1, 1.01);
    single->DataCollectionSingleton::writeTimeInfo(r1, 1.02);
    
    single->DataCollectionSingleton::writeDistanceInfo(d1, 1.01);
    single->DataCollectionSingleton::writeDistanceInfo(r1, 1.02);

    single->DataCollectionSingleton::writeAccountInfo(d1, 1.01);
    single->DataCollectionSingleton::writeAccountInfo(r1, 1.02);

    single->DataCollectionSingleton::writeBatteryUsage(d1, 23);
    single->DataCollectionSingleton::writeNumberOfTrips(d1, 10);

    single->DataCollectionSingleton::writeToCSV();

    delete single;

    delete d1;
    delete r1;
    delete d2;
    delete r2;
    delete d3;
    delete r3;
}