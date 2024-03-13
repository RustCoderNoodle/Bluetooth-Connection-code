#include <XBOXONE.h>
#include <SPI.h>

USB Usb;
XBOXONE Xbox(&Usb);

void setup() {
    Serial.begin(9600);
    if (Usb.Init() == -1) {
        Serial.print(F("\r\nOSC did not start"));
        while (1); //halt
    }
    Serial.print(F("\r\nXBOX USB Library Started"));
}

void loop() {
    Usb.Task();
    if (Xbox.XboxOneConnected) {
        int LHX = Xbox.getAnalogHat(LeftHatX);
        int LHY = Xbox.getAnalogHat(LeftHatY);
        int LA2 = Xbox.getButtonPress(L2);
        int RA2 = Xbox.getButtonPress(R2);
        int LFT = Xbox.getButtonPress(LEFT);
        int RHT = Xbox.getButtonPress(RIGHT);
        int start_button = Xbox.getButtonPress(XBOX);

        // Send data over serial to ESP32
        Serial.print(LHX);
        Serial.print("\t");
        Serial.print(LHY);
        Serial.print("\t");
        Serial.print(LA2);
        Serial.print("\t");
        Serial.print(RA2);
        Serial.print("\t");
        Serial.print(LFT);
        Serial.print("\t");
        Serial.print(RHT);
        Serial.print("\t");
        Serial.print(start_button);
        Serial.println();
    }
}
//
// Created by noodle on 3/13/2024.
//

#include "XboxCode.h"
