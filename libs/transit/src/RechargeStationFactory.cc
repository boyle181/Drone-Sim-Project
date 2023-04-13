#include "RechargeStationFactory.h"

IEntity* RechargeStationFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("rechargeStation") == 0) {
    std::cout << "Recharge Station Created" << std::endl;
    return new RechargeStation(entity);
  }
  return nullptr;
}