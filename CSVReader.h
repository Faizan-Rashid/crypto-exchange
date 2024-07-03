// create a function that will read contents of csv file into a vector of OrderBookEntry object.
#pragma once

#ifndef CSVREADER_H
#define CSVREADER_H

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
public:
    CSVReader();
    // all are static so as we can access them without creating instance.
    static std::vector<OrderBookEntry> readCSV(std::string);
    static std::vector<std::string> tokenise(std::string, char);
    static OrderBookEntry stringToOBE(std::string price, std::string amount, std::string timestamp, std::string product, OrderBookType orderType);

private:
    static OrderBookEntry stringToOBE(std::vector<std::string>);
};
#endif