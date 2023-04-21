#ifndef WALLET_DECORATOR_H_
#define WaLLET_DECORATOR_H_
#include "IEntity.h"
#include "Robot.h"
#include "Drone.h"
#include "IStrategy.h"
#include "graph.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include <iostream>
#include <cstring>
#include <cstdlib>



/**
 * @brief this class inherits from the IStrategy class. It is used 
 * to create changeable and trackable wallets inside drones and robots.
 */
class WalletDecorator : public IEntity {

 public:

  /**
   * @brief Wallet is created with a random preset total money value
   * @param entity a pointer IEntity object in which the wallet is created
   */
   WalletDecorator(IEntity* entity);

   void Update(double dt, std::vector<IEntity*> scheduler);
   
 private:
   IStrategy* getStrategy();

   IEntity* component;
   double account = 0;
   std::string type;
   bool clientValid;                      // Keeps track if a client has been cleared for ride
   const double START_MONEY = 1000.00;
   const int RANGE = 1000;
   const double COST_FOR_TRIP = 20.00;     // Cost per unit of time (trip)
   const double COST_FOR_RECHARGE = 10.00; // Cost per unit of time (recharge)
};

#endif  