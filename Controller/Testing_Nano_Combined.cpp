#include <XBOXONE.h>
#include <SoftwareSerial.h>

USB Usb;
XBOXONE Xbox(&Usb);
SoftwareSerial SerialBT(2, 3); // RX, TX pins for Bluetooth module
const int ledPin = 13; // Pin for LED

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(9600);
    delay(1000);
    Serial.println("Initializing Bluetooth communication...");

    // Initialize serial communication with Bluetooth module
    SerialBT.begin(9600);
    delay(1000);
    Serial.println("Bluetooth communication initialized.");

    // Initialize Xbox controller
    if (Usb.Init() == -1) {
        Serial.println(F("\r\nOSC did not start"));
        while (1); // Halt
    }
    Serial.println(F("\r\nXBOX USB Library Started"));

    pinMode(ledPin, OUTPUT); // Set LED pin as output
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
        int B_button = Xbox.getButtonPress(B);

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

        // Check if B button is pressed, turn on LED if true
        if (B_button) {
            digitalWrite(ledPin, HIGH); // Turn on LED
        } else {
            digitalWrite(ledPin, LOW); // Turn off LED
        }
    }

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
