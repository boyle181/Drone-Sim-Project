#include "RobotFactory.h"

#include "WalletDecorator.h"

IEntity* RobotFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("robot") == 0) {
    // return new WalletDecorator (new Robot(entity));
    // Robot* robot = new Robot(entity);
    // return (new WalletDecorator(robot));
    return new Robot(entity);
    std::cout << "Robot Created" << std::endl;
  }
  return nullptr;
}
