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

/**
 * Constructs an empty inventory object
 */
Inventory::Inventory() {

}

/**
 * Destructs an inventory object
 */
Inventory::~Inventory() {
    // TODO: deconstruct inventory
}

/**
 * Adds an item to the inventory
 *
 * @param item                      item to add to inventory
 */
void Inventory::add(StockItem *item) {
    this->stock.push_back(item);

    // Increase stock count in inventory hashmap for this component type
    this->stockCount[item->getComponentType()] += item->getStockAmount();
}

/**
 * Retrieves the amount of stock of a given component type
 *
 * @param componentType             the component typeto check for
 * @return                          amount of stock for the component type
 */
int Inventory::getStockCount(const string &componentType) {
    // TODO: get StockCount error checking may be required
    return this->stockCount[componentType];
}

/**
 * Removes an item from the inventory
 *
 * @param item                      item to remove from inventory
 */
void Inventory::remove(StockItem &item) {
    // TODO: remove item from inventory

    this->stockCount[item.getComponentType()] -= item.getStockAmount();
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
 * @param increasing                set to true to have in increasing order,
 *                                  false for decreasing order
 */
void Inventory::sortByPrice(bool increasing) {
    // TODO: ensure sort works correctly
    sort(this->stock.begin(), this->stock.end());
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
 * Overloads the output operator to stream details about the inventory.
 *
 * @param os                        the output stream to send info to
 * @param inventory                 inventory to stream info about
 * @return                          outstream with inventory information
 */
ostream &operator<<(ostream &os, Inventory &inventory) {
    os << "Inventory Size: " << inventory.getSize() << endl;

    for (StockItem *item : inventory.stock) {
        os << *item << endl;
    }

    return os;
}
