#ifndef WALLET_DECORATOR_H_
#define WaLLET_DECORATOR_H_
#include "IEntity.h"




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
   
  /**
   * @brief pays off the debt the wallet has accumlated
   */
   void payDebt();
   
  /**
   * @brief Gets the wallet value in the wallet
   * @return Returns the current wallet value
   */
   double getAccount();

   void Update(double dt, std::vector<IEntity*> scheduler);
   
 private:
   IEntity* component;
   double account = 0;
   double debt = 0;
};

#endif  