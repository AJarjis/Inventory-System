/******************************************************************************
 *
 * File        : Inventory.cpp
 *
 * Date        : 21 March 2018
 *
 * Description : A file to define an inventory system of a company.
 *
 * Author      : Ali Jarjis
 *
 ******************************************************************************/

#include <algorithm>
#include "Inventory.h"

using namespace std;

/**
 * Constructs an empty inventory object
 */
Inventory::Inventory() {
}

/**
 * Destructs an inventory object
 */
Inventory::~Inventory() {
    for (StockItem *item : this->stock) {
        delete item;
    }
}

/**
 * Copy constructor for inventory object
 *
 * @param inv           inventory to copy
 */
Inventory::Inventory(const Inventory &inv) {
    // Allocates space for stock
    this->stock.reserve(inv.getSize());

    // Copies passed inventory stock into this inventory
    for (int i = 0; i < inv.getSize(); i++) {
        this->stock.push_back(inv.stock.at(i));
    }
}

/**
 * Copy assignment operator for inventory object
 *
 * @param inv           inventory to assign
 * @return              reference to copy of inventory object
 */
Inventory &Inventory::operator=(const Inventory &inv) {
    // Checks for self-assignment
    if (this != &inv) {
        // Clears this inventory's stock before starting copy
        this->stock.clear();

        // Allocates space for stock
        this->stock.reserve(inv.getSize());

        // Copies passed inventory stock into this inventory
        for (int i = 0; i < inv.getSize(); i++) {
            this->stock.push_back(inv.stock.at(i));
        }
    }

    return *this;
}

/**
 * Adds an item to the inventory
 *
 * @param item                      item to add to inventory
 */
void Inventory::add(StockItem *item) {
    this->stock.push_back(item);
}

/**
 * Retrieves the amount of items in the inventory
 *
 * @return                          amount of items in inventory
 */
int Inventory::getSize() const {
    return this->stock.size();
}

/**
 * Sorts the inventory by price
 *
 * @param ascending                 set to true to have in increasing order,
 *                                  false for decreasing order
 */
void Inventory::sortByPrice(bool ascending) {
    // Lambda for comparing two stock items by price
    auto comparisionMethod = [ascending](const StockItem *item1,
                                         const StockItem *item2) -> bool {
        // Comparision method changes if wanting to sort ascending/descending
        if (ascending == true) {
            return item1->getUnitPrice() < item2->getUnitPrice();
        } else {
            return item1->getUnitPrice() > item2->getUnitPrice();
        }
    };

    // Sorts the vector of stock items
    sort(this->stock.begin(), this->stock.end(), comparisionMethod);
}


/**
 * Searches for a particular component type
 *
 * @param componentType             component type to search for
 * @return                          search results of components that match
 */
vector<StockItem *> Inventory::search(const string &componentType) {
    vector<StockItem *> searchResults;

    // Loops through stock adding any matches found to search result
    for (StockItem *item : this->stock) {
        if (item->getComponentType() == componentType) {
            searchResults.push_back(item);
        }
    }

    return searchResults;
}

/**
 * Overloads the [] operator to allow array-like access to the stock
 *
 * @param i                 index of element
 * @return                  stock item stored at position
 */
StockItem *Inventory::operator[](int i) {
    return this->stock[i];
}

/**
 * Overloads the output operator to stream details about the inventory.
 *
 * @param os                        the output stream to send info to
 * @param inventory                 inventory to stream info about
 * @return                          outstream with inventory information
 */
ostream &operator<<(ostream &os, Inventory &inventory) {
    os << "Inventory Size: " << inventory.getSize() << endl << endl;

    // Prints each item in inventory
    for (StockItem *item : inventory.stock) {
        os << *item << endl;
    }

    return os;
}
