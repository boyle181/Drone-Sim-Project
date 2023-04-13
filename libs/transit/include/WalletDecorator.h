#ifndef WALLET_DECORATOR_H_
#define WaLLET_DECORATOR_H_

#include "IEntity.h"
class WalletDecorator : public IEntity {

 public:
    WalletDecorator(IEntity* entity);
    void addMoney(double money);
    bool subtractMoney(double money);
    int getAccount();
 private:
    IEntity* component;
    double account;
};

#endif  