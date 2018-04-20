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
#include <sstream>

#include "StockItem.h"
#include "Inventory.h"

using namespace std;

// Reads and loads in an inventory file
Inventory readInventoryFile(string &file);

// Trims whitespace of a given string
string &trim(string &str);

// Answers their respective questions from the worksheet
void answerQuestion1(Inventory &inv);
void answerQuestion2(Inventory &inv);
void answerQuestion3(Inventory &inv);
void answerQuestion4(Inventory &inv);
void answerQuestion5(Inventory &inv);



int main(int argc, char **argv) {
    // Loads up inventory
    string inventoryFileName = "inventory.txt";
    Inventory charltinsInventory = readInventoryFile(inventoryFileName);

    answerQuestion1(charltinsInventory);

    answerQuestion2(charltinsInventory);

    answerQuestion3(charltinsInventory);

    answerQuestion4(charltinsInventory);

    answerQuestion5(charltinsInventory);

    return EXIT_SUCCESS;
}

/**
 * Prints a list of the inventory, sorted in order of increasing price.
 *
 * @param inv           inventory to answer questions with
 */
void answerQuestion1(Inventory &inv) {
    inv.sortByPrice(true);
    cout << "Question 1:" << endl << inv;
}

/**
 * Prints component with the largest number of components in stock.
 *
 * @param inv           inventory to answer questions with
 */
void answerQuestion2(Inventory &inv) {
    // Stores details on component with highest stock amount
    StockItem *maxStockItem;
    int maxStockAmount = 0;

    // For each item retrieves its stock amount comparing with maximum
    for (int i = 0; i < inv.getSize(); i++) {
        StockItem *item = inv[i];

        int stockAmount = item->getStockAmount();

        // Checks if this item beats the maximum stock amount,
        // replacing it if true
        if (maxStockAmount < stockAmount) {
            maxStockItem = item;
            maxStockAmount = stockAmount;
        }
    }

    cout << "Question 2: " << endl
         << "The component with the largest number of components in stock is: "
         << endl << *maxStockItem << endl;
}

/**
 * Prints amount of NPN transistors in stock.
 *
 * @param inv           inventory to answer questions with
 */
void answerQuestion3(Inventory &inv) {
    string componentType = "Transistor";
    DeviceType deviceType = DeviceType::NPN;
    int totalStock = 0;

    // Gets all transistors in inventory
    vector<StockItem *> transistorInventory = inv.search(componentType);

    // For each transistor check if it is an NPN and increment the total stock
    for (StockItem *item : transistorInventory) {
        // Casts item to transistor to be able to access transistor methods
        Transistor *transistor = dynamic_cast<Transistor *>(item);

        if (transistor->getDeviceType() == deviceType) {
            totalStock += transistor->getStockAmount();
        }
    }

    cout << "Question 3: " << endl << "There are " << totalStock
         << " NPN transistors in stock" << "." << endl << endl;
}

/**
 * Prints total resistance of all resistors in stock.
 *
 * @param inv           inventory to answer questions with
 */
void answerQuestion4(Inventory &inv) {
    string componentType = "Resistor";
    double totalResistance = 0;

    // Gets all resistors in inventory
    vector<StockItem *> resistorInventory = inv.search(componentType);

    // For each resistor check if it is in stock and increment total resistance
    for (StockItem *item : resistorInventory) {
        // Casts item to resistor to be able to access resistor methods
        Resistor *resistor = dynamic_cast<Resistor *>(item);

        // Increases total resistance if in stock
        if (resistor->getStockAmount() > 0) {
            totalResistance += resistor->getResistance();
        }
    }

    cout << "Question 4: " << endl
         << "The total resistance of all resistors in stock is "
         << fixed << setprecision(2) << totalResistance << " ohms ." << endl
         << endl;
}

/**
 * Prints amount of stock items with a unit price above 10p.
 *
 * @param inv           inventory to answer questions with
 */
void answerQuestion5(Inventory &inv) {
    int priceLimit = 10;
    int stockItemsAboveLimit = 0;

    inv.sortByPrice(false);

    // Loops through inventory, incrementing count if item price is above 10
    for (int i = 0; i < inv.getSize(); i++) {
        StockItem *item = inv[i];

        // Checks if item price is above 10, breaks early due to inventory
        // being sorted meaning no need to carry on searching
        if (item->getUnitPrice() > priceLimit) {
            stockItemsAboveLimit++;
        } else {
            break;
        }
    }

    cout << "Question 5: " << endl << "Amount of stock items above "
         << priceLimit << "p is " << stockItemsAboveLimit << "." << endl
         << endl;
}

/**
 * Reads and loads in an inventory file
 *
 * @param file              inventory file to read in
 * @return                  inventory object filled with data from file
 */
Inventory readInventoryFile(string &file) {
    Inventory inv;

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

            try {
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
                                                    stoi(stockItemDetails.at(
                                                            2)),
                                                    stoi(stockItemDetails.at(
                                                            3)),
                                                    stockItemDetails.at(4));
                } else {
                    throw invalid_argument(
                            "Invalid component " + stockItemDetails.at(0) +
                            " could not be added");
                }

                // Adds the newly created item to inventory
                inv.add(newItem);

            } catch (exception e) {
                cerr << "Failed to add item to inventory." << endl;
            }


        }
    } else {
        cerr << "Unable to open file " << file << endl;
    }

    fileStream.close();

    return inv;
}

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

