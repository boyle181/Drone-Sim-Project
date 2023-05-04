#include "RechargeStation.h"

RechargeStation::RechargeStation(JsonObject &obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position =  {Random(-1400, 1500), position.y, Random(-800, 800)};
  direction = {0, 0, 0};
  speed = 0;
  available = true;
}



RechargeStation::~RechargeStation() {
  // Delete dynamically allocated variables
  delete graph;
}