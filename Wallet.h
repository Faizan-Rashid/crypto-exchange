#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <map>

class Wallet
{
public:
    Wallet();
    // insert currency to wallet
    void insertCurrency(std::string type, double amount);
    // remove currency from the wallet
    bool removeCurrency(std::string type, double amount);
    // check if wallet has enough currency or more
    bool containsCurrency(std::string type, double amount);
    // check if the wallet can cope with this ask or bid
    bool canFulfillOrder(OrderBookEntry order);
    // update content of wallet assumes order was made by owner of wallet
    void processSale(OrderBookEntry &sale);
    // generate string representation of wallet
    std::string toString();

private:
    // for mapping between curriency types and amounts
    std::map<std::string, double> curriencies;
};
