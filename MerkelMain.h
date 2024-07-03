#pragma once // include header file only once

#ifndef MERKELMAIN_H
#define MERKELMAIN_H

#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include <vector>
#include <string>

class MerkelMain
{
public:
    MerkelMain();
    void init();

private: // private member functions
    // print menu options Lists
    void printMenu();
    // get user's choice
    int getUserOption();
    // validate and process user options
    void processUserOption(int);
    // functions for processing userOption() switch-case
    void printHelp();
    void printMarketStatus();
    void enterAsk();
    void enterBid();
    void printWallet();
    void goToNextTimeFrame();

    std::string currentTime;

    OrderBook orderBook{"20200317.csv"}; // aggregation
    Wallet wallet;//aggregation
};
#endif