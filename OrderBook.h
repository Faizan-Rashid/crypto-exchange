#pragma once

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>

class OrderBook
{
public:
    OrderBook(std::string fileName);
    // return product string vector of all know in dataset
    std::vector<std::string> getKnownProducts();
    // return vector of all order as per filters given
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    // returns the earliest time in the orderBook
    std::string getEarliestTime();
    // returns the next time after the set time in the orderbook, if there is no next timestamp, start from the first.if you go to end wrap it back around.
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry& order);
    // static, as it not works on it's own orders.
    static double getHighPrice(std::vector<OrderBookEntry> &orders);
    static double getLowestPrice(std::vector<OrderBookEntry> &orders);
    //matching engine algorithm
    std::vector<OrderBookEntry> matchAsksToBids(std::string products,std::string timestamp);

private:
    std::vector<OrderBookEntry> orders;
};

#endif