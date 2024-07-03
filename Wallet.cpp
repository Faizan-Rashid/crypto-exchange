#include "Wallet.h"
#include "CSVReader.h"
#include <exception> //for checking balance
#include <iostream>
#include <string>

Wallet::Wallet()
{
}
// implement insert capability of wallet
void Wallet::insertCurrency(std::string type, double amount)
{
    // exception handling in-case -ve amount passed.
    double balance;
    try
    {
        if (amount < 0)
            throw std::exception{};
    }
    catch (const char *error)
    {
        std::cout << error;
    }
    // checking if wallet has "type" curriency
    if (curriencies.count(type) == 0) // not there yet
    {
        balance = 0;
    }
    else
    {
        balance = curriencies[type];
    }
    // increment balance whether "type" currency is present in certain amount or not.
    balance += amount;
    // update the wallet
    curriencies[type] = balance;
}

// implemention removeCurrency()
bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0)
        return false;
    // checking if wallet has "type" currency
    if (curriencies.count(type) == 0)
    {
        false;
    }
    else
    {
        // if wallet has enough currency only then update it.
        if (containsCurrency(type, amount))
            curriencies[type] -= amount;
        else
            return false;
    }
}

// implement bidding capability of wallet
bool Wallet::containsCurrency(std::string type, double amount)
{
    if (curriencies.count(type) == 0)
        return false; // wallet doesnot have this curriency
    else
        return curriencies[type] >= amount; // return false if amount in that currency is less than required amount.
}

// implementing toString()
std::string Wallet::toString()
{
    std::string s; // store message
    // pair represents one of members of curriencies. loop iterate through each pair of map
    for (std::pair<std::string, double> pair : curriencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
        // to_string used to convert double to string type
    }
    return s;
}

// implement canFulfillOreder()
bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "\nWallet::canFulfillOrder " << currency << " : " << amount;
        return containsCurrency(currency, amount);
    }
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        std::cout << "\nWallet::canFulfillOrder " << currency << " : " << amount;
        return containsCurrency(currency, amount);
    }
    return false;
}

// processSale()
void Wallet::processSale(OrderBookEntry &sale)
{
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    if (sale.orderType == OrderBookType::askSale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        curriencies[incomingCurrency] += incomingAmount;
        curriencies[outgoingCurrency] -= outgoingAmount;
    }
    if (sale.orderType == OrderBookType::bidSale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        curriencies[incomingCurrency] += incomingAmount;
        curriencies[outgoingCurrency] -= outgoingAmount;
    }
}