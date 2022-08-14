
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
#include "OLED-Display-SOLDERED.h"

#include "splash.h"

INA219 inaP;
INA219 inaN;

OLED_Display display;

float voltageP = 0;
float voltageN = 0;
float currentP = 0;
float currentN = 0;

void setupIna219() {
    inaP.begin(0x40);
    inaN.begin(0x44);

    inaP.configure(INA219_RANGE_16V, INA219_GAIN_80MV, INA219_BUS_RES_12BIT, INA219_SHUNT_RES_12BIT_16S);
    inaN.configure(INA219_RANGE_16V, INA219_GAIN_80MV, INA219_BUS_RES_12BIT, INA219_SHUNT_RES_12BIT_16S);

    // Calibrate INA219. Rshunt = 0.1 ohm, Max excepted current = 800 mA
    inaP.calibrate(0.1, 0.8);
    inaN.calibrate(0.1, 0.8);
}

void setupDisplay() {  
    if (!display.begin()) {
        Serial.println("Display init failed!");
        for (;;)
            ;
    }

    display.clearDisplay();
    drawLogo();
    display.display();

    delay(2000);

    display.clearDisplay();
    display.display();
}

void setup() {
    Serial.begin(115200);
    
    setupIna219();
    setupDisplay();
}

//void processMeasure() {
//    voltageP = inaP.readBusVoltage();
//    currentP = abs(inaP.readShuntCurrent() * 1000);
//
//    voltageN = inaN.readBusVoltage();
//    currentN = abs(inaN.readShuntCurrent() * 1000);
//}

// Read values in loop
void loop() {
//    processMeasure();
//
//    Serial.println("+12V Rail:");
//    Serial.print("  Voltage: ");
//    Serial.print(voltageP, 2);
//    Serial.println(" V");
//    Serial.print("  Current: ");
//    Serial.print(currentP, 1);
//    Serial.println(" mA");
//
//    Serial.println("-12V Rail:");
//    Serial.print("  Voltage: ");
//    Serial.print(voltageN, 2);
//    Serial.println(" V");
//    Serial.print("  Current: ");
//    Serial.print(currentN, 1);
//    Serial.println(" mA");
//
//    Serial.println("");
//    delay(1000);
}

void drawLogo(void)
{
    display.clearDisplay();

    display.drawBitmap((display.width() - LOGO_WIDTH) / 2, (display.height() - LOGO_HEIGHT) / 2, logo_bmp, LOGO_WIDTH,
                       LOGO_HEIGHT, 1);
    display.display();
    delay(1000);
}