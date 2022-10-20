
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

#include "Configuration.h"

#define PIN_12V A0

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

    inaP.configure(INA219_RANGE_32V, INA219_GAIN_80MV, INA219_BUS_RES_12BIT, INA219_SHUNT_RES_12BIT_16S);
    inaN.configure(INA219_RANGE_32V, INA219_GAIN_80MV, INA219_BUS_RES_12BIT, INA219_SHUNT_RES_12BIT_16S);

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

    delay(SPLASH_DURATION);

    display.clearDisplay();
    display.display();
}

void setup() {
    Serial.begin(115200);
    
    setupIna219();
    setupDisplay();
}

void processMeasure() {
    voltageP = abs(inaP.readBusVoltage());
    voltageN = -analogRead(PIN_12V) * 0.0049 * MULTI_VOLT_N;
    voltageP = (voltageP + voltageN) * MULTI_VOLT_P;

    currentP = abs(inaP.readShuntCurrent() * 1000) * MULTI_CURR_P + OFFS_CURR_P;
    currentN = abs(inaN.readShuntCurrent() * 1000) * MULTI_CURR_N + OFFS_CURR_N;
}

void processDisplay() {
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(4, 6);
    display.print("+12V:");

    display.setTextSize(1);
    String strVoltageP = String(voltageP, 2) + " V";
    drawRightString(strVoltageP, 118,  4);
    String strCurrentP = String(currentP, 1) + "  mA";
    drawRightString(strCurrentP, 124,  15);

    display.drawLine(0, 29, 127, 29, SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(4, 40);
    display.print("-12V:");

    display.setTextSize(1);
    String strVoltageN = String(voltageN, 2) + " V";
    drawRightString(strVoltageN, 118,  38);
    String strCurrentN = String(currentN, 1) + "  mA";
    drawRightString(strCurrentN, 124,  49);

    display.display();
}

void loop() {
    processMeasure();
    processDisplay();

    delay(SAMPLE_RATE);
}

void drawLogo(void) {
    display.drawBitmap((display.width() - LOGO_WIDTH) / 2, (display.height() - LOGO_HEIGHT) / 2, logo_bmp, LOGO_WIDTH,
                       LOGO_HEIGHT, 1);
}

void drawRightString(String buf, int x, int y) {
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(x - w, y);
    display.print(buf);
}