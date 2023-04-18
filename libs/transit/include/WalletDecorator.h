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
   * @brief Adds more money to the wallet value
   * @param money An int which is added to the total wallet value
   */
   void addMoney(double money);
   
  /**
   * @brief Takes in an amount, tests whether it can be removed from wallet value
   * total, then either returns false if it is too much, or returns true and removes
   * the amount from the current wallet value
   * @param amount An int which is removed to the total wallet value
   * @return Returns true if usage removed amount from wallet value 
   * or false if it failed to do so
   */
   bool subtractMoney(double money);
   
  /**
   * @brief Gets the wallet value in the wallet
   * @return Returns the current wallet value
   */
   double getAccount();

   void Update(double dt, std::vector<IEntity*> scheduler);
   
 private:
   IEntity* component;
   double account;
};

#endif  