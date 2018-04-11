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

#include "StockItem.h"
#include "Inventory.h"

using namespace std;

/**
 * Reads and loads in an inventory file
 * @param file              inventory file to read in
 * @param inv               inventory object to load data into
 */
void readInventoryFile(string &file, Inventory &inv) {
    ifstream fileStream(file);

    if (fileStream) {
        string line;

        while (getline(fileStream, line)) {
            string compType;
            getline(fileStream, compType, ',' );

            string stockCode;
            getline(fileStream, stockCode, ',' );

            cout << compType << stockCode << endl;

//            int stockAmount;
//            getline(fileStream, stockAmount, ', ' );
//
//            int unitPrice;
//            getline(fileStream, unitPrice, ', ' );


//            StockItem *newItem;
//
//            if (compType == "Resistor") {
//                string resistanceCode;
//                newItem = new Resistor(stockCode, stockAmount, unitPrice,
//                                       resistanceCode);
//            } else if (compType == "Capacitors") {
//                string capacitanceCode;
//                newItem = new Capacitor(stockCode, stockAmount, unitPrice,
//                                        capacitanceCode);
//            } else if (compType == "Transistor") {
//                string deviceType;
//                newItem = new Transistor(stockCode, stockAmount, unitPrice,
//                                         deviceType);
//            } else if (compType == "Diode") {
//                newItem = new Diode(stockCode, stockAmount, unitPrice);
//            } else if (compType == "Integrated Circuit") {
//                string description;
//                newItem = new IntegratedCircuit(stockCode, stockAmount,
//                                                unitPrice, description);
//            } else {
//                cerr << "Invalid component " << compType
//                     << " could not be added" << endl;
//            }

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
    string inventoryFileName = "../inventory.txt";

    readInventoryFile(inventoryFileName, charltinsInventory);


//    Resistor* res = new Resistor("Code", 5, 4, "5M1");
//    Resistor* res2 = new Resistor("Code", 5, 4, "5R1");
//    Capacitor* cap = new Capacitor("CapCode", 5, 4, "2400uf");
//    Diode* dio = new Diode("DioCode", 5, 4);
//    Transistor* tra = new Transistor("tracode", 5, 4, "PNP");
//    IntegratedCircuit* ic = new IntegratedCircuit("iccode", 5, 4, "sdfdsfdsfjkdsfhdsjkfhskfhsdfjsdhfkjs");
//
//    Inventory* inv = new Inventory();
//
//    inv->add(res);
//    inv->add(res2);
//    inv->add(cap);
//    inv->add(dio);
//    inv->add(tra);
//    inv->add(ic);
//
//    inv->sortByPrice(true);
//
//    vector<StockItem*> results = inv->search("Diode");

    // QUESTION 1
    // charltinsInventory.sortByPrice(false);
    // cout << "Question 1:" << endl << endl
    //      << *charltinsInventory << endl;

    // QUESTION 2
    // string compTypes[] = {"Resistor", "Capacitors", "Transistors", "Diode",
    //                       "Integrated Circuits"};
    // loop through comptypes calling getStockCount to get maximum

    // QUESTION 3
    // Vector<Resistor*> resistorInventory = charltinsInventory.search("Resistor");
    // loop through resistorInventory incrementing stock amount if transistor is npn

    // QUESTION 4
    // loop through resistorInventory incrementing total resistance if in stock

    //QUESTION 5
    // loop through charltinsInventory incrementing if unit price is above 10


    return 0;
}

