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

// STOCKITEM CODE

/**
 * Constructs a new stock item with the given details,
 *
 * @param code                  stock code of item
 * @param amount                stock amount
 * @param price                 unit price of item
 */
StockItem::StockItem(const string &code, int amount, int price) {
    this->stockCode = code;

    this->setStockAmount(amount);

    this->setUnitPrice(amount);
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
    if (amount > 0) {
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
        : StockItem(code, price, amount) {
    this->resistance = calculateResistance(resistanceCode);
}

/**
 * Retrieves the component type (resistor)
 *
 * @return                      string detailing type of component
 */
string Resistor::getComponentType() {
    return "Resistor";
}

/**
 * Retrieves the resistance of this item in Ohms
 *
 * @return                      resistance of item
 */
int Resistor::getResistance() const {
    return this->resistance;
}

/**
 * Sets the resistance of an item given it's code value
 *
 * @param resistanceCode        code representing resistance
 */
void Resistor::setResistance(const string &resistanceCode) {
    this->resistance = calculateResistance(resistanceCode);
}

/**
 * Calculates the resistance from a resistance code
 *
 * @param resistanceCode        resistor code to calculate
 * @return                      resistance of item
 */
double Resistor::calculateResistance(string resistanceCode) {
    int specialCharAmount = 1;

    // iterates through code converting special characters to a
    // decimal point to then be multiplied by
    for (char &c : resistanceCode) {
        if (c == 'M') {
            c = '.';
            specialCharAmount = 1000000;
        } else if (c == 'K') {
            c = '.';
            specialCharAmount = 1000;
        } else if (c == 'R') {
            c = '.';
            specialCharAmount = 1;
        }
    }

    // Stores final resistance value in ohms
    double ohms = stod(resistanceCode) * specialCharAmount;

    return ohms;
}

/**
 * Overloads the output operator to stream details specific to a resistor.
 *
 * @param os                    the output stream to send info to
 * @param resistor              resistor to stream info about
 * @return                      outstream with resistor info
 */
ostream &operator<<(ostream &os, Resistor &resistor) {
    return os << "Component Type: " << resistor.getComponentType() << endl
              << "Stock Code: " << resistor.stockCode << endl
              << "Stock Amount: " << resistor.stockAmount << endl
              << "Unit Price: " << resistor.unitPrice << "p" << endl
              << "Total Resistance: " << resistor.resistance << "ohms" << endl;
    // TODO: ensure resistance and capacitance is printed out correctly
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
        : StockItem(code, price, amount) {
    this->capacitance = convertToPicoFarads(capacitance);
}

/**
 * Retrieves the component type (capacitor)
 *
 * @return                      string detailing type of component
 */
string Capacitor::getComponentType() {
    return "Capacitor";
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
void Capacitor::setCapacitance(string &capacitance) {
    this->capacitance = convertToPicoFarads(capacitance);
}

/**
 * Converts capacitance to picofarads
 *
 * @param capacitance               capacitance as string e.g 100pf, 10nf
 * @return                          capacitance of item in picofarads
 */
double Capacitor::convertToPicoFarads(string capacitance) {
    string picoFaradString;
    double picoFaradAmount = 0;

    // Loops through each character in the capacitance string,
    // to figure out the capacitance in picofarads
    for (char &c : capacitance) {
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
 * Overloads the output operator to stream details specific to a capacitor.
 *
 * @param os                        the output stream to send info to
 * @param capacitor                 capacitor to stream info about
 * @return                          outstream with capacitor info
 */
ostream &operator<<(ostream &os, Capacitor &capacitor) {
    return os << "Component Type: " << capacitor.getComponentType() << endl
              << "Stock Code: " << capacitor.stockCode << endl
              << "Stock Amount: " << capacitor.stockAmount << endl
              << "Unit Price: " << capacitor.unitPrice << "p" << endl
              << "Total Capacitance: " << capacitor.capacitance << "pf" << endl;
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
        : StockItem(code, price, amount) {}

/**
* Retrieves the component type (diode)
*
* @return                      string detailing type of component
*/
string Diode::getComponentType() {
    return "Diode";
}

/**
 * Overloads the output operator to stream details specific to a diode.
 *
 * @param os                        the output stream to send info to
 * @param diode                     diode to stream info about
 * @return                          outstream with capacitor info
 */
ostream &operator<<(ostream &os, Diode &diode) {
    return os << "Component Type: " << diode.getComponentType() << endl
              << "Stock Code: " << diode.stockCode << endl
              << "Stock Amount: " << diode.stockAmount << endl
              << "Unit Price: " << diode.unitPrice << "p" << endl;
}

// DEVICE TYPE (ENUM) CODE

/**
 * Overloads the output operator to stream name of a device.
 *
 * @param os                        the output stream to send info to
 * @param deviceType                deviceType to stream name about
 * @return                          outstream with deviceType name
 */
ostream &operator<<(ostream &os, const Device &deviceType) {
    switch (deviceType) {
        case Device::NPN :
            return os << "NPN";
        case Device::PNP :
            return os << "PNP";
        case Device::FET :
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
        : StockItem(code, amount, price) {
    this->setDeviceType(deviceType);
}

/**
* Retrieves the component type (transistor)
*
* @return                      string detailing type of component
*/
string Transistor::getComponentType() {
    return "Transistor";
}

/**
 * Retrieves the device type of this transistor
 *
 * @return                          device type of transistor
 */
Device Transistor::getDeviceType() const {
    return this->deviceType;
}

/**
 * Sets the device type of a transistor
 *
 * @param deviceType                new device type of transistor
 */
void Transistor::setDeviceType(const string &deviceType) {
    Device newDeviceType;

    // Converts from string to Device enum type
    if (deviceType == "NPN") {
        newDeviceType = Device::NPN;
    } else if (deviceType == "PNP") {
        newDeviceType = Device::PNP;
    } else if (deviceType == "FET") {
        newDeviceType = Device::FET;
    } else {
        throw invalid_argument("Invalid device type for transistor.");
    }

    this->deviceType = newDeviceType;
}

/**
 * Overloads the output operator to stream details specific to a transistor.
 *
 * @param os                        the output stream to send info to
 * @param transistor                transistor to stream info about
 * @return                          outstream with transistor info
 */
ostream &operator<<(ostream &os, Transistor &transistor) {
    return os << "Component Type: " << transistor.getComponentType() << endl
              << "Stock Code: " << transistor.stockCode << endl
              << "Stock Amount: " << transistor.stockAmount << endl
              << "Unit Price: " << transistor.unitPrice << "p" << endl
              << "Device Type: " << transistor.deviceType << endl;
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
        : StockItem(code, amount, price) {
    this->description = description;
}

/**
* Retrieves the component type (Integrated Circuit)
*
* @return                      string detailing type of component
*/
string IntegratedCircuit::getComponentType() {
    return "Integrated Circuit";
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
 * Overloads the output operator to stream details specific to an
 * integrated circuit.
 *
 * @param os                        the output stream to send info to
 * @param item                      integrated circuit to stream info about
 * @return                          outstream with integrated circuit info
 */
ostream &operator<<(ostream &os, IntegratedCircuit &integratedCircuit) {
    return os << "Component Type: " << integratedCircuit.getComponentType()
              << endl << "Stock Code: " << integratedCircuit.stockCode << endl
              << "Stock Amount: " << integratedCircuit.stockAmount << endl
              << "Unit Price: " << integratedCircuit.unitPrice << "p" << endl
              << "Description: " << integratedCircuit.description << endl;
}
