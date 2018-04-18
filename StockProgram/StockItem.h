/******************************************************************************
 *
 * File        : StockItem.h
 *
 * Date        : 21 March 2018
 *
 * Description : A header file to define an abstract stock item and the 
 *               concrete classes {resistors, capacitors, diodes, transistors, 
 *               integrated circuits}.
 *
 * Author      : Ali Jarjis
 *
 ******************************************************************************/

#ifndef STOCKITEM_H
#define STOCKITEM_H

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * Models an abstract stock item
 */
class StockItem {
protected:
    // Item's component type (resistor, capacitor, diode, etc)
    string componentType;

    // Unique stock code of an item.
    string stockCode;

    // Number of items left in stock.
    int stockAmount;

    // Unit price of item stored in pence.
    int unitPrice;

    // StockItem Constructor
    StockItem(const string &compType, const string &code, int amount,
              int price);

public:
    // Retrieves the component type of a stock item - abstract method
    string getComponentType();

    // Retrieves stock code of item
    string getStockCode() const;

    // Retrieves stock amount of item
    int getStockAmount() const;

    // Retrieves unit price of item
    int getUnitPrice() const;

    // Sets the stock code of item
    void setStockCode(const string &code);

    // Sets the stock amount of item
    void setStockAmount(int amount);

    // Sets the unit price of item
    void setUnitPrice(int price);

    // Provides details of this object for output stream
    // (helper method for output operator, must be overriden by sub classes)
    virtual ostream &print(ostream &os) const = 0;

    // Output operator for stock items
    friend ostream &operator<<(ostream &os, const StockItem &item);
};

/**
 * Models a resistor stock item
 */
class Resistor : public StockItem {
private:
    // Resistor's resistance in Ohms
    double resistance;

public:
    // Resistor Constructor
    Resistor(const string &code, int amount, int price,
             const string &resistanceCode);

    // Retrieves the resistance of this resistor in ohms
    double getResistance() const;

    // Set resistance amount using code
    void setResistance(const string &resistanceCode);

    // Converts a resistor's code value to resistance in ohms
    double calculateResistance(string resistanceCode);

    // Provides details of resistor in output stream
    ostream &print(ostream &os) const override;
};

/**
 * Models a capacitor stock item
 */
class Capacitor : public StockItem {
private:
    //Capacitor's capacitance in picofarads
    double capacitance;

public:
    // Capacitor constructor
    Capacitor(const string &code, int amount, int price,
              const string &capacitance);

    // Retrieves capacitance of capacitor
    int getCapacitance() const;

    // Set capacitance amount of capacitor
    void setCapacitance(string &capacitance);

    // Converts capacitance string into picofarads
    double convertToPicoFarads(string capacitance);

    // Provides details of capacitor as a string
    ostream &print(ostream &os) const override;
};

/**
 * Models a diode stock item
 */
class Diode : public StockItem {
private:
public:
    // Diode constructor
    Diode(const string &code, int amount, int price);

    // Provides details of diode as a string
    ostream &print(ostream &os) const override;
};

// Device types for a transistor
enum class DeviceType {
    NPN, PNP, FET
};

/**
 * Models a transistor stock item
 */
class Transistor : public StockItem {
private:
    // Indication of device type {NPN, PNP, FET}
    DeviceType deviceType;

public:
    // Transistor constructor
    Transistor(const string &code, int amount, int price,
               const string &deviceType);

    // Retrieves the device type of this transistor
    DeviceType getDeviceType() const;

    // Sets the device type of a transistor
    void setDeviceType(const string &deviceType);

    // Provides details of transistor as a string
    ostream &print(ostream &os) const override;
};

/**
 * Models a integrated circuit stock item
 */
class IntegratedCircuit : public StockItem {
private:
    // Brief description of integrated circuit
    string description;

public:
    // IntegratedCircuit constructor
    IntegratedCircuit(const string &code, int amount, int price,
                      const string &description);

    // Retrieves the description of this integrated circuit
    string getDescription() const;

    // Sets the description of an integrated circuit
    void setDescription(const string &description);

    // Provides details of intergrated circuit as a string
    ostream &print(ostream &os) const override;
};

#endif /* STOCKITEM_H */