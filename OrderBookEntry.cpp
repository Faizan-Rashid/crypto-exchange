#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(std::string timestamp, std::string product, OrderBookType orderType, double price, double amount, std::string username)
{
    this->timestamp = timestamp;
    this->product = product;
    this->orderType = orderType;
    this->price = price;
    this->amount = amount;
}

// implementing stringToOrderBookType()
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
    if (s == "ask")
        return OrderBookType::ask;
    if (s == "bid")
        return OrderBookType::bid;
    return OrderBookType::unknown;
}
