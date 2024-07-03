// what user can experience. use functions for refactoring(avoid repetition in main()).
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    MerkelMain app{}; // calling default constructor
    app.init();
    Wallet wallet;
    wallet.insertCurrency("BTC", 10);
    wallet.insertCurrency("ETH", 10000);
    std::cout << "\nwallet in string is " << wallet.toString() << std::endl;
    // wallet.removeCurrency("BTC", 5);
    // std::cout << wallet.toString() << std::endl;
    return 0;
}
