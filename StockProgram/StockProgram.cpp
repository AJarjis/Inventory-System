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

#include "StockItem.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Resistor res("Code", 5, 4, "5M1");
    Capacitor cap("CapCode", 5, 4, "2400uf");
    Diode dio("DioCode", 5, 4);
    Transistor tra("tracode", 5, 4, "type");
    IntegratedCircuit ic("iccode", 5, 4, "sdfdsfdsfjkdsfhdsjkfhskfhsdfjsdhfkjs");

    cout << res << endl;
    cout << cap << endl;
    cout << dio << endl;
    cout << tra << endl;
    cout << ic << endl;

    return 0;
}

