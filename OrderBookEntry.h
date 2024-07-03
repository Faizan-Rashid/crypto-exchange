#pragma once

#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H

#include <string>
#include <iostream>

// using a string to represent orderType can result in any value but we have only 2 variants(bid & ask), so we use enum.using class keyword prevents naming conflicts as data is encapsulated on enum.
enum class OrderBookType
{
    ask,
    bid,
    askSale,
    bidSale,
    unknown
};

class OrderBookEntry
{
public:
    double price;
    double amount;
    std::string product;
    std::string timestamp;
    OrderBookType orderType; // aggregation
    std::string username;

public:
    OrderBookEntry(std::string timestamp = "", std::string product = "", OrderBookType orderType = OrderBookType::bid, double price = 0.0, double amount = 0.0, std::string username = "dataset");
    
    static bool compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.timestamp < e2.timestamp;
    }
    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price < e2.price;
    }
    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price > e2.price;
    }
    static OrderBookType stringToOrderBookType(std::string);
    void printMembers()
    {
        std::cout << "\nprice: " << price;
        std::cout << "\n:amount " << amount;
        std::cout << "\n:product " << product;
        std::cout << "\n:time stamp " << timestamp;
        // std::cout<<"\n: "<<;
    }
};
#endif