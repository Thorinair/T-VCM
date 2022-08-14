
/**
 **************************************************
 *
 * @file        INA219-Simple.ino
 * @brief       INA219 Zero-Drift, Bi-directional Current/Power Monitor. Simple Example.
 *
 *
 *  product: www.solde.red/333075
 *
 * @authors     Korneliusz Jarzebski
 * 
 *          Modified by soldered.com
 ***************************************************/

#include "INA219-SOLDERED.h"

#include "INA219Helper.h"

INA219 inaP;
INA219 inaN;

float voltageP = 0;
float voltageN = 0;
float currentP = 0;
float currentN = 0;

void setupIna219() {
    Serial.println("Initialize INA219");
    Serial.println("-----------------------------------------------");

    // Default INA219 address is 0x40
    inaP.begin(0x40);
    inaN.begin(0x44);

    // Configure INA219
    inaP.configure(INA219_RANGE_16V, INA219_GAIN_80MV, INA219_BUS_RES_12BIT, INA219_SHUNT_RES_12BIT_16S);
    inaN.configure(INA219_RANGE_16V, INA219_GAIN_80MV, INA219_BUS_RES_12BIT, INA219_SHUNT_RES_12BIT_16S);

    // Calibrate INA219. Rshunt = 0.1 ohm, Max excepted current = 800 mA
    inaP.calibrate(0.1, 0.8);
    inaN.calibrate(0.1, 0.8);

    // Display configuration
    Serial.println("+12V Rail:");
    checkConfig(inaP);
    Serial.println("");
    Serial.println("-12V Rail:");
    checkConfig(inaN);

    Serial.println("-----------------------------------------------");
}

void setup() {
    Serial.begin(115200);
    
    setupIna219();
}

void processMeasure() {
    voltageP = inaP.readBusVoltage();
    currentP = abs(inaP.readShuntCurrent() * 1000);

    voltageN = inaN.readBusVoltage();
    currentN = abs(inaN.readShuntCurrent() * 1000);
}

// Read values in loop
void loop() {
    processMeasure();

    Serial.println("+12V Rail:");
    Serial.print("  Voltage: ");
    Serial.print(voltageP, 2);
    Serial.println(" V");
    Serial.print("  Current: ");
    Serial.print(currentP, 1);
    Serial.println(" mA");

    Serial.println("-12V Rail:");
    Serial.print("  Voltage: ");
    Serial.print(voltageN, 2);
    Serial.println(" V");
    Serial.print("  Current: ");
    Serial.print(currentN, 1);
    Serial.println(" mA");

    Serial.println("");
    delay(1000);
}