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
    // Unique stock code of an item.
    string stockCode;

    // Number of items left in stock.
    int stockAmount;

    // Unit price of item stored in pence.
    int unitPrice;

    // StockItem Constructor
    StockItem(const string &code, int amount, int price);

public:
    // Retrieves the component type of a stock item - abstract method
    virtual string getComponentType() = 0;

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

    // Retrieves the component type (resistor)
    string getComponentType() override;

    // Retrieves the resistance of this resistor in ohms
    int getResistance() const;

    // Set resistance amount using code
    void setResistance(const string &resistanceCode);

    // Converts a resistor's code value to resistance in ohms
    double calculateResistance(string resistanceCode);

    // Output operator for resistor
    friend ostream &operator<<(ostream &os, Resistor &resistor);
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

    // Retrieves the component type (capacitor)
    string getComponentType() override;

    // Retrieves capacitance of capacitor
    int getCapacitance() const;

    // Set capacitance amount of capacitor
    void setCapacitance(string &capacitance);

    // Converts capacitance string into picofarads
    double convertToPicoFarads(string capacitance);

    // Output operator for capacitor
    friend ostream &operator<<(ostream &os, Capacitor &capacitor);
};

/**
 * Models a diode stock item
 */
class Diode : public StockItem {
private:
public:
    // Diode constructor
    Diode(const string &code, int amount, int price);

    // Retrieves the component type (diode)
    string getComponentType() override;

    // Output operator for diode
    friend ostream &operator<<(ostream &os, Diode &diode);
};

enum class Device {NPN, PNP, FET};

/**
 * Models a transistor stock item
 */
class Transistor : public StockItem {
private:
    // Indication of device type {NPN, PNP, FET}
    Device deviceType;

public:
    // Transistor constructor
    Transistor(const string &code, int amount, int price,
               const string &deviceType);

    // Retrieves the component type (transistor)
    string getComponentType() override;

    // Retrieves the device type of this transistor
    Device getDeviceType() const;

    // Sets the device type of a transistor
    void setDeviceType(const string &deviceType);

    // Output operator for transistor
    friend ostream &operator<<(ostream &os, Transistor &transistor);
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

    // Retrieves the component type (Integrated Circuit)
    string getComponentType() override;

    // Retrieves the description of this integrated circuit
    string getDescription() const;

    // Sets the description of an integrated circuit
    void setDescription(const string &description);

    // Output operator for transistor
    friend ostream &
    operator<<(ostream &os, IntegratedCircuit &integratedCircuit);
};

#endif /* STOCKITEM_H */