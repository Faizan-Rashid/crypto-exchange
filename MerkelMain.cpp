#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <string>
#include <vector>

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // Lists
    //  print help
    std::cout << "\n1: Print help";
    // print exchange statistics
    std::cout << "\n2: see exchange statistics";
    // make an offer
    std::cout << "\n3: make an offer";
    // make a bid
    std::cout << "\n4: make a bid";
    // see wallet
    std::cout << "\n5: see wallet";
    // continue
    std::cout << "\n6: continue";

    std::cout << "\n==============";
    std::cout << "\ncurrent time is " << currentTime << std::endl;
}
int MerkelMain::getUserOption()
{
    int userOption;
    std::string line;
    std::cout << "type in 1-6\n";
    std::getline(std::cin, line);
    try
    {
        userOption = stod(line);
    }
    catch (const std::exception &error)
    {
    }
    return userOption;
}
void MerkelMain::processUserOption(int userOption)
{
    // validating
    while (userOption < 1 || userOption > 6)
    {
        std::cout << "invalid number.\nSelect Your choice again between 1 - 6 only or exit by pressing 0.\n";
        std::cin >> userOption;
        if (userOption == 0)
            break;
    }
    // implementing Lists
    switch (userOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printMarketStatus();
        break;
    case 3:
        enterAsk();
        break;
    case 4:
        enterBid();
        break;
    case 5:
        printWallet();
        break;
    case 6:
        goToNextTimeFrame();
        break;
    default:
        break;
    }
}
// implementing processUserOption switch cases functions.
void MerkelMain::printHelp()
{
    std::cout << "\nHelp - your aim is to make money. Analyse the market and bids and offers.";
}
void MerkelMain::printMarketStatus()
{
    for (std::string const &p : orderBook.getKnownProducts())
    {
        std::cout << "\nProduct " << p;
        // return entried with these filters
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "\nasks seen: " << entries.size();
        std::cout << "\nmax ask: " << OrderBook::getHighPrice(entries);
        std::cout << "\nmin ask: " << OrderBook::getLowestPrice(entries);
    }
}
void MerkelMain::enterAsk()
{
    std::string input;
    std::cout << "\nMake an ask - enter product, amount and price e.g, ETH/BTC, 2.00, 0.0923";
    // std::cin.ignore();
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "\nMerkelMain::enterAsk bad input ";
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "\nwallet looks good. ";
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "\nwallet has insufficient funds.";
            }
        }
        catch (const std::exception &error)
        {
            std::cout << "\nMerkelMain::enterAsk() - bad input";
        }
    }
}
void MerkelMain::enterBid()
{
    std::string input;
    std::cout << "\nMake a bid- enter product, amount and price e.g, ETH/BTC, 2.00, 0.0923";
    // std::cin.ignore();
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "\nMerkelMain::enterBid bad input ";
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "\nwallet looks good. ";
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "\nwallet has insufficient funds.";
            }
        }
        catch (const std::exception &error)
        {
            std::cout << "\nMerkelMain::enterBid() - bad input";
        }
    }
}
void MerkelMain::printWallet()
{
    std::cout << "\n"
              << wallet.toString();
}
void MerkelMain::goToNextTimeFrame()
{
    std::cout << "\nGoing to next time frame.";
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "\nmatching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "\ntotal sales " << sales.size();
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "\nsale price: " << sale.price << " amount " << sale.amount;
            if (sale.username == "simuser")
            {
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}
