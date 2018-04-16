/******************************************************************************
 *
 * File        : StockProgram.cpp
 *
 * Date        : 21 March 2018
 *
 * Description : Main part of the stock program, deals with loading and 
 *               processing data and answers queries.
 *
 * Author      : Ali Jarjis
 *
 ******************************************************************************/


#include <cstdlib>
#include <fstream>
#include <cstring>
#include <sstream>


#include "StockItem.h"
#include "Inventory.h"

using namespace std;

/**
 * Trims whitespace of a given string
 *
 * Please note that this has been modified from a version of another trim
 * function found here:
 * http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
 *
 * @param str               string to trim whitespace of
 * @return                  trimmed string
 */
string &trim(string &str) {
    const string whiteSpace = "\t\n\v\f\r ";

    // Removes whitespace from end of string
    str.erase(str.find_last_not_of(whiteSpace) + 1);

    // Removes whitespace from front of string
    str.erase(0, str.find_first_not_of(whiteSpace));

    return str;
}

/**
 * Reads and loads in an inventory file
 * @param file              inventory file to read in
 * @param inv               inventory object to load data into
 */
void readInventoryFile(string &file, Inventory &inv) {
    ifstream fileStream(file);

    if (fileStream) {
        string line;
        const char DELIMITER = ',';

        // For each line in the file, creates a stock item
        while (getline(fileStream, line)) {
            // Allows line to be manipulated as a stream so as to store each
            // word on the line
            stringstream stringStream(line);
            string word;

            // Stores the details of a stock item from a line
            vector<string> stockItemDetails;

            // For each word on a line trim whitespace and add to list
            while (getline(stringStream, word, DELIMITER)) {
                trim(word);
                stockItemDetails.push_back(word);
            }

            StockItem *newItem;

            // Creates a new stock item of the correct type
            if (stockItemDetails.at(0) == "resistor") {
                newItem = new Resistor(stockItemDetails.at(1),
                                       stoi(stockItemDetails.at(2)),
                                       stoi(stockItemDetails.at(3)),
                                       stockItemDetails.at(4));
            } else if (stockItemDetails.at(0) == "capacitor") {
                newItem = new Capacitor(stockItemDetails.at(1),
                                        stoi(stockItemDetails.at(2)),
                                        stoi(stockItemDetails.at(3)),
                                        stockItemDetails.at(4));
            } else if (stockItemDetails.at(0) == "transistor") {
                newItem = new Transistor(stockItemDetails.at(1),
                                         stoi(stockItemDetails.at(2)),
                                         stoi(stockItemDetails.at(3)),
                                         stockItemDetails.at(4));
            } else if (stockItemDetails.at(0) == "diode") {
                newItem = new Diode(stockItemDetails.at(1),
                                    stoi(stockItemDetails.at(2)),
                                    stoi(stockItemDetails.at(3)));
            } else if (stockItemDetails.at(0) == "IC") {
                newItem = new IntegratedCircuit(stockItemDetails.at(1),
                                                stoi(stockItemDetails.at(2)),
                                                stoi(stockItemDetails.at(3)),
                                                stockItemDetails.at(4));
            } else {
                cerr << "Invalid component " << stockItemDetails.at(0)
                     << " could not be added" << endl;
            }

            // Adds the newly created item to inventory
            inv.add(newItem);

        }
    } else {
        cerr << "Unable to open file " << file << endl;
    }

    fileStream.close();
}

/*
 * 
 */
int main(int argc, char **argv) {
    Inventory charltinsInventory;
    string inventoryFileName = "inventory.txt";

    readInventoryFile(inventoryFileName, charltinsInventory);

    // TODO: QUESTION 1
//     charltinsInventory.sortByPrice(false);
//     cout << "Question 1:" << endl << endl
//          << charltinsInventory << endl;

    // QUESTION 2
    string compTypes[] = {"Resistor", "Capacitor", "Transistor", "Diode",
                          "Integrated Circuit"};

    // Stores details on component with highest stock amount
    string maxComponent;
    int maxStockAmount = 0;

    // For each component type retrieves its stock amount comparing with maximum
    for (string &type : compTypes) {
        int stockAmount = charltinsInventory.getStockCount(type);

        if (maxStockAmount < stockAmount) {
            maxComponent = type;
            maxStockAmount = stockAmount;
        }
    }

    cout << "Question 2: " << maxComponent
         << " has the largest number of components in stock with "
         << maxStockAmount << "." << endl;

    // QUESTION 3
    string componentTypeQ3 = "Transistor";
    string deviceTypeQ3 = "NPN";
    int totalStockQ3 = 0;

    // Stores all transistors in inventory
    vector<Transistor *> transistorInventory
            = charltinsInventory.search(componentTypeQ3);

    // For each transistor check if it is an NPN and increment the total stock
    for (Transistor *transistor : transistorInventory) {
        if (transistor->getDeviceType() == deviceTypeQ3) {
            totalStockQ3 += transistor->getStockAmount();
        }
    }

    cout << "Question 3: " << "There are " << totalStockQ3
         << " NPN transistors in stock" << endl;

    // QUESTION 4
    // loop through resistorInventory incrementing total resistance if in stock

    //QUESTION 5
    // loop through charltinsInventory incrementing if unit price is above 10


    return 0;
}

