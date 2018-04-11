/******************************************************************************
 *
 * File        : Inventory.h
 *
 * Date        : 21 March 2018
 *
 * Description : A header file to define an inventory system of a company.
 *
 * Author      : Ali Jarjis
 *
 ******************************************************************************/

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <map>
#include "StockItem.h"

using namespace std;

class Inventory {
private:
    // Stores the inventory of stockitems
    vector<StockItem *> stock;

    // Stores the stock amount for each component type
    map<string, int> stockCount;
public:
    // Inventory Constructor
    Inventory();

    // Inventory Destructor
    virtual ~Inventory();

    // Adds an item to the inventory
    void add(StockItem *item);

    // Removes an item from the inventory
    void remove(StockItem &item);

    // Retrieves the amount of stock of a given component type
    int getStockCount(const string& componentType);

    // Retrieves the amount of items in the inventory
    int getSize() const;

    // Sorts the inventory by price (increasing/decreasing)
    void sortByPrice(bool decreasing);

    // Searches for an array of items in the inventory
    vector<StockItem *> search(const string& searchTerm);

    // Output operator for inventory
    friend ostream &operator<<(ostream &os, Inventory &inventory);
};

#endif /* INVENTORY_H */

