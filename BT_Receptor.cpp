#include <SoftwareSerial.h>

SoftwareSerial SerialBT(2, 3); // RX, TX pins for Bluetooth module

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(9600);
    delay(1000);
    Serial.println("Initializing Bluetooth communication...");

    // Initialize serial communication with Bluetooth module
    SerialBT.begin(9600);
    delay(1000);
    Serial.println("Bluetooth communication initialized.");
}

void loop() {
    if (SerialBT.available()) {
        // If data is available from Bluetooth module, read and print it
        char c = SerialBT.read();
        Serial.print(c);
    }

    if (Serial.available()) {
        // If data is available from serial monitor, send it to Bluetooth module
        char c = Serial.read();
        SerialBT.write(c);
    }
}
