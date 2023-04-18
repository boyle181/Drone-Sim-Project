#include "RechargeStation.h"

RechargeStation::RechargeStation(JsonObject &obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  direction = {0, 0, 0};
  speed = 0;
  available = true;
}

RechargeStation::~RechargeStation() {
  // Delete dynamically allocated variables
  delete graph;
}