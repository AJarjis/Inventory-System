/******************************************************************************
 *
 * File        : StockItem.cpp
 *
 * Date        : 21 March 2018
 *
 * Description : A file to define an abstract stock item and the concrete 
 *               classes {resistors, capacitors, diodes, transistors, 
 *               integrated circuits}.
 *
 * Author      : Ali Jarjis
 *
 ******************************************************************************/

#include "StockItem.h"

using namespace std;

// STOCKITEM CODE

/**
 * Constructs a new stock item with the given details,
 *
 * @param compType              component type of item
 * @param code                  stock code of item
 * @param amount                stock amount
 * @param price                 unit price of item
 */
StockItem::StockItem(const string &compType, const string &code, int amount,
                     int price) {
    this->componentType = compType;
    this->stockCode = code;

    this->setStockAmount(amount);
    this->setUnitPrice(price);
}

/**
 * Retrieves the component type of an item
 *
 * @return                      item's component type
 */
string StockItem::getComponentType() {
    return this->componentType;
}

/**
 * Retrieves the stock code of this item
 *
 * @return                      stock code of item
 */
string StockItem::getStockCode() const {
    return this->stockCode;
}

/**
 * Retrieves the stock amount of this item
 *
 * @return                      stock amount of item
 */
int StockItem::getStockAmount() const {
    return this->stockAmount;
}

/**
 * Retrieves the unit price of this item
 *
 * @return                      unit price of item
 */
int StockItem::getUnitPrice() const {
    return this->unitPrice;
}

/**
 * Sets the stock code of an item to a new code
 *
 * @param code                  new stock code
 */
void StockItem::setStockCode(const string &code) {
    this->stockCode = code;
}

/**
 * Sets the stock amount of an item to a new amount
 *
 * @param amount                new stock amount
 */
void StockItem::setStockAmount(int amount) {
    // Error checking for stock amount ensuring it must be greater than zero
    if (amount >= 0) {
        this->stockAmount = amount;
    } else {
        throw invalid_argument("Stock amount for item must be greater than 0.");
    }
}

/**
 * Sets the unit price of an item to a new price
 *
 * @param price                 new unit price
 */
void StockItem::setUnitPrice(int price) {
    // Error checking for unit price ensuring it must be greater than zero
    if (price > 0) {
        this->unitPrice = price;
    } else {
        throw invalid_argument("Unit price for item must be greater than 0.");
    }
}

/**
 * Overloads the output operator to stream details specific to the item.
 *
 * @param os                    the output stream to send info to
 * @param item                  stock item to stream info about
 * @return                      outstream with resistor info
 */
ostream &operator<<(ostream &os, const StockItem &item) {
    return item.print(os);
}

// RESISTOR CODE

/**
 * Constructs a new resistor with the given details,
 *
 * @param code                  stock code of item
 * @param amount                stock amount
 * @param price                 unit price of item
 * @param resistanceCode        code representing resistance
 */
Resistor::Resistor(const string &code, int amount, int price,
                   const string &resistanceCode)
        : StockItem("Resistor", code, amount, price) {
    this->setResistance(resistanceCode);
}

/**
 * Retrieves the resistance of this item in Ohms
 *
 * @return                      resistance of item
 */
double Resistor::getResistance() const {
    return this->resistance;
}

/**
 * Sets the resistance of an item given it's code value
 *
 * @param resistanceCode        code representing resistance
 */
void Resistor::setResistance(const string &resistanceCode) {
    this->resistance = Resistor::calculateResistance(resistanceCode);
}

/**
 * Calculates the resistance from a resistance code
 *
 * @param resistanceCode        resistor code to calculate
 * @return                      resistance of item
 */
double Resistor::calculateResistance(string resistanceCode) {
    double specialCharAmount = 1;

    // iterates through code converting special characters to a
    // decimal point to then be multiplied by
    for (char &c : resistanceCode) {
        switch (c) {
            case ('M'): {
                c = '.';
                specialCharAmount = 1000000;
                break;
            }
            case ('K'): {
                c = '.';
                specialCharAmount = 1000;
                break;
            }
            case ('R'): {
                c = '.';
                specialCharAmount = 1;
                break;
            }
        }
    }

    // Stores final resistance value in ohms
    double ohms = stod(resistanceCode) * specialCharAmount;

    return ohms;
}

/**
 * Provides details of resistor in output stream
 *
 * @param os                   the output stream to send info to
 * @return                     outstream with resistor info
 */
ostream &Resistor::print(ostream &os) const {
    return os << "Component Type: " << this->componentType << endl
              << "Stock Code: " << this->stockCode << endl
              << "Stock Amount: " << this->stockAmount << endl
              << "Unit Price: " << this->unitPrice << "p" << endl
              << "Total Resistance: " << fixed << setprecision(2)
              << this->resistance << "ohms" << endl;
}

// CAPACITORS CODE

/**
 * Constructs a new capacitor with the given details,
 *
 * @param code                      stock code of item
 * @param amount                    stock amount
 * @param price                     unit price of item
 * @param capacitance               capacitance as string e.g 100pf, 10nf
 */
Capacitor::Capacitor(const string &code, int amount, int price,
                     const string &capacitance)
        : StockItem("Capacitor", code, amount, price) {
    this->setCapacitance(capacitance);
}

/**
 * Retrieves the capacitance of this item in Farads
 *
 * @return                          capacitance of item
 */
int Capacitor::getCapacitance() const {
    return this->capacitance;
}

/**
 * Sets the capacitance of an item (in millifarads)
 *
 * @param capacitance               capacitance as string e.g 100pf, 10nf
 */
void Capacitor::setCapacitance(const string &capacitance) {
    this->capacitance = Capacitor::convertToPicoFarads(capacitance);
}

/**
 * Converts capacitance to picofarads
 *
 * @param capacitance               capacitance as string e.g 100pf, 10nf
 * @return                          capacitance of item in picofarads
 */
double Capacitor::convertToPicoFarads(const string capacitance) {
    string picoFaradString;
    double picoFaradAmount = 0;

    // Loops through each character in the capacitance string,
    // to figure out the capacitance in picofarads
    for (const char &c : capacitance) {
        // Stores number values only in picoFaradString
        if (isdigit(c)) {
            picoFaradString += c;
        } else {
            // Performs conversion to picofarads once suffix is reached
            picoFaradAmount = stoi(picoFaradString);

            switch (c) {
                case 'm' : { // Convert millifards to picofarads
                    double millifaradConversion = 1.0E-9;
                    picoFaradAmount /= millifaradConversion;
                    break;
                }
                case 'u' : { // Convert microfarads to picofarads
                    double microfaradConversion = 1.0E-6;
                    picoFaradAmount /= microfaradConversion;
                    break;
                }
                case 'n' : { // Convert nanofarads to picofarads
                    double nanofaradConversion = 0.001;
                    picoFaradAmount /= nanofaradConversion;
                    break;
                }
            }
            break;
        }
    }

    return picoFaradAmount;
}

/**
 * Provides details of capacitor in output stream
 *
 * @param os                   the output stream to send info to
 * @return                     outstream with capacitor info
 */
ostream &Capacitor::print(ostream &os) const {
    return os << "Component Type: " << this->componentType << endl
              << "Stock Code: " << this->stockCode << endl
              << "Stock Amount: " << this->stockAmount << endl
              << "Unit Price: " << this->unitPrice << "p" << endl
              << "Total Capacitance: " << fixed << setprecision(0)
              << this->capacitance << "pf" << endl;
}

// DIODE CODE

/**
 * Constructs a new diode with the given details,
 *
 * @param code                      stock code of item
 * @param amount                    stock amount
 * @param price                     unit price of item
 */
Diode::Diode(const string &code, int amount, int price)
        : StockItem("Diode", code, amount, price) {

}

/**
 * Provides details of diode in output stream
 *
 * @param os                   the output stream to send info to
 * @return                     outstream with diode info
 */
ostream &Diode::print(ostream &os) const {
    return os << "Component Type: " << this->componentType << endl
              << "Stock Code: " << this->stockCode << endl
              << "Stock Amount: " << this->stockAmount << endl
              << "Unit Price: " << this->unitPrice << "p" << endl;
}

// DEVICE TYPE (ENUM) CODE

/**
 * Overloads the output operator to stream name of a device.
 *
 * @param os                        the output stream to send info to
 * @param deviceType                deviceType to stream name about
 * @return                          outstream with deviceType name
 */
ostream &operator<<(ostream &os, const DeviceType &deviceType) {
    switch (deviceType) {
        case DeviceType::NPN :
            return os << "NPN";
        case DeviceType::PNP :
            return os << "PNP";
        case DeviceType::FET :
            return os << "FET";
        default:
            return os;
    }
}

// TRANSISTOR CODE

/**
 * Constructs a new transistor with the given details,
 *
 * @param code                      stock code of item
 * @param amount                    stock amount
 * @param price                     unit price of item
 * @param deviceType                device type of transistor
 */
Transistor::Transistor(const string &code, int amount, int price,
                       const string &deviceType)
        : StockItem("Transistor", code, amount, price) {
    this->setDeviceType(deviceType);
}

/**
 * Retrieves the device type of this transistor
 *
 * @return                          device type of transistor
 */
DeviceType Transistor::getDeviceType() const {
    return this->deviceType;
}

/**
 * Sets the device type of a transistor
 *
 * @param deviceType                new device type of transistor
 */
void Transistor::setDeviceType(const string &deviceType) {
    DeviceType newDeviceType;

    // Converts from string to Device enum type
    if (deviceType == "NPN") {
        newDeviceType = DeviceType::NPN;
    } else if (deviceType == "PNP") {
        newDeviceType = DeviceType::PNP;
    } else if (deviceType == "FET") {
        newDeviceType = DeviceType::FET;
    } else {
        throw invalid_argument("Invalid device type for transistor.");
    }

    this->deviceType = newDeviceType;
}

/**
 * Provides details of transistor in output stream
 *
 * @param os                   the output stream to send info to
 * @return                     outstream with transistor info
 */
ostream &Transistor::print(ostream &os) const {
    return os << "Component Type: " << this->componentType << endl
              << "Stock Code: " << this->stockCode << endl
              << "Stock Amount: " << this->stockAmount << endl
              << "Unit Price: " << this->unitPrice << "p" << endl
              << "Device Type: " << this->deviceType << endl;
}

// INTEGRATED CIRCUITS CODE

/**
 * Constructs a new integrated circuit with the given details,
 *
 * @param code                      stock code of item
 * @param amount                    stock amount
 * @param price                     unit price of item
 * @param description               integrated circuit description
 */
IntegratedCircuit::IntegratedCircuit(const string &code, int amount, int price,
                                     const string &description)
        : StockItem("Integrated Circuit", code, amount, price) {
    this->description = description;
}

/**
 * Retrieves the description of this integrated circuit
 *
 * @return                          integrated circuit description
 */
string IntegratedCircuit::getDescription() const {
    return this->description;
}

/**
 * Sets the description of an integrated circuit
 *
 * @param description               new integrated circuit description
 */
void IntegratedCircuit::setDescription(const string &description) {
    this->description = description;
}

/**
 * Provides details of integrated circuit in output stream
 *
 * @param os                   the output stream to send info to
 * @return                     outstream with integrated circuit info
 */
ostream &IntegratedCircuit::print(ostream &os) const {
    return os << "Component Type: " << this->componentType << endl
              << "Stock Code: " << this->stockCode << endl
              << "Stock Amount: " << this->stockAmount << endl
              << "Unit Price: " << this->unitPrice << "p" << endl
              << "Description: " << this->description << endl;
}
