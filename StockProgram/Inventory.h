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

class Inventory {
private:
    // Stores the inventory of stockitems
    std::vector<StockItem *> stock;
public:
    // Inventory Constructor
    Inventory();

    // Inventory Destructor
    virtual ~Inventory();

    // Inventory Copy Constructor
    Inventory(const Inventory &inv);

    // Inventory Copy Assignment Operator Overload
    Inventory &operator=(const Inventory &inv);

    // Adds an item to the inventory
    void add(StockItem *item);

    // Retrieves the amount of items in the inventory
    int getSize() const;

    // Sorts the inventory by price (increasing/decreasing)
    void sortByPrice(bool decreasing);

    // Searches for an array of items in the inventory
    std::vector<StockItem *> search(const std::string &componentType);

    // Allows for array like access to inventory
    StockItem *operator[](int i);

    // Output operator for inventory
    friend std::ostream &operator<<(std::ostream &os, Inventory &inventory);
};

#endif /* INVENTORY_H */

