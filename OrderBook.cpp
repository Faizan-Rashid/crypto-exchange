#include "OrderBook.h"
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <map>
#include <algorithm>

OrderBook::OrderBook(std::string fileName)
{
    orders = CSVReader::readCSV(fileName);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;
    for (OrderBookEntry &e : orders)
    {
        prodMap[e.product] = true;
    } // at the end we'll have uniques things(keys) int the map
    for (auto const &e : prodMap)
    {
        products.push_back(e.first); // strings of products
    }
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry &e : orders)
    {
        if (e.orderType == type && e.product == product && e.timestamp == e.timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

// implement getHighPrice()
double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price > max)
            max = e.price;
    }
    return max;
}

// implement getHighPrice()
double OrderBook::getLowestPrice(std::vector<OrderBookEntry> &orders)
{
    double lowest = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price < lowest)
            lowest = e.price;
    }
    return lowest;
}

// implement the getEarliestTime()
std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

// implementing getNextTime()
std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
        next_timestamp == orders[0].timestamp;
    // std::cout << "\ntimestamp " << next_timestamp;
    // std::cout << true << std::endl;
    return next_timestamp;
}

// implement insertOrder()
void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

// implement matchAsksToBids
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string products, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, products, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, products, timestamp);
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry &ask : asks)
    {
        for (OrderBookEntry &bid : bids)
        {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{timestamp, products, OrderBookType::askSale, ask.price, 0};
                if (bid.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidSale;
                }
                if (ask.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::askSale;
                }

                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                };
                if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                };
                if (bid.amount < ask.amount && bid.amount > 0)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue; // go to next bid as ask isn't fulfilled completely
                };
            }
        }
    }
    return sales;
}
