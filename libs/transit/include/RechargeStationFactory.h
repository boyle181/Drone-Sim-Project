#ifndef RECHARGESTATION_FACTORY_H_
#define RECHARGESTATION_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"

/**
 *@brief Recharge Station Factory to produce recharge station class.
 **/
class RechargeStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~RechargeStationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
