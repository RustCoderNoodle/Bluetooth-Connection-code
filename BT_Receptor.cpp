#include <BluetoothSerial.h>

BluetoothSerial SerialBT; // Create an instance of the BluetoothSerial class

void setup() {
    Serial.begin(9600); // Initialize serial communication for debugging purposes
    SerialBT.begin("ESP32_BT"); // Start Bluetooth with the name "ESP32_BT"
    Serial.println("Bluetooth initialized");
}

void loop() {
    // Your main code here
}
