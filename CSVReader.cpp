
#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <string>

// #include <string>
CSVReader::CSVReader()
{
}
// implementing CSVReader()
std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile(csvFilename);
    std::string line;
    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception &error)
            {
                std::cout << "\nCSVReader::readCSV bad file. " << std::endl;
            };
            // std::cout << "\nCSVReader::readCSV size. " << entries.size() << std::endl;
        }
        csvFile.close();
    }
    else
        std::cout << "\nerror opening file.";
    return entries;
}

// implementing tokenise() functions
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == end || start == csvLine.length())
            break;
        if (end >= 0)
        { // means spearator found
            token = csvLine.substr(start, end - start);
        }
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);
    return tokens;
}

// implementing stringToOBE() function[converts strings to order book entry object]
OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    if (tokens.size() != 5) // checking for line completion
    {
        std::cout << "\nbad line. tokens size is " << tokens.size();
        throw std::exception();
    }
    // we have complete 5 parameters in line

    // stod() converts string to double. throws error if it doesn't receive valid string of numbers.
    try
    {
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        std::cout << "\nCSVReader::stringToOBE() not a valid float! " << tokens[3] << std::endl;
        std::cout << "\nCSVReader::stringToOBE() not a valid float! " << tokens[4] << std::endl;
        throw; // throw the exception
    }
    OrderBookEntry obe{tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2]), price, amount};
    return obe;
}

// implementing overloaded stringToOBE()
OrderBookEntry CSVReader::stringToOBE(std::string priceString, std::string amountString, std::string timestamp, std::string product, OrderBookType orderType)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception &e)
    {
        std::cout << "\nCSVReader::stringToOBE() not a valid float! " << priceString << std::endl;
        std::cout << "\nCSVReader::stringToOBE() not a valid float! " << amountString << std::endl;
        throw; // throw the exception
    }
    OrderBookEntry obe{timestamp, product, orderType, price, amount};
    return obe;
}