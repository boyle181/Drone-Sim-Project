#include "DroneFactory.h"
#include "WalletDecorator.h"


IEntity* DroneFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    // IEntity *decorator = new WalletDecorator(new Drone(entity));
    // return (new WalletDecorator(new Drone));
    return new Drone(entity);
    std::cout << "Drone Created" << std::endl;
  }
  return nullptr;
}
