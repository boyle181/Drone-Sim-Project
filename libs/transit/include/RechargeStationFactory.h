// Copyright 2023 Jason Paciorek, Aidan Boyle, Rebecca Hoff, Nuh Misirli

#ifndef LIBS_TRANSIT_INCLUDE_RECHARGESTATIONFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_RECHARGESTATIONFACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "RechargeStation.h"

/**
 *@brief Recharge Station Factory to produce recharge station class.
 **/
class RechargeStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  ~RechargeStationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully,
   * or a nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_RECHARGESTATIONFACTORY_H_
