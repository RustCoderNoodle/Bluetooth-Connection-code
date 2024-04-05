//
// Created by noodle on 4/3/2024.
//
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

BLEServer* pServer;
BLECharacteristic* pCharacteristic;

#define MOTOR_LEFT_ENA 5
#define MOTOR_LEFT_IN1 18
#define MOTOR_LEFT_IN2 19
#define MOTOR_RIGHT_ENB 13
#define MOTOR_RIGHT_IN3 14
#define MOTOR_RIGHT_IN4 27

void setup() {
    Serial.begin(9600);

    // Initialize BLE
    BLEDevice::init("YourESP32"); // Name of your ESP32
    pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
            CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE
    );
    pService->start();
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

    // Initialize motor pins as outputs
    pinMode(MOTOR_LEFT_ENA, OUTPUT);
    pinMode(MOTOR_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_LEFT_IN2, OUTPUT);
    pinMode(MOTOR_RIGHT_ENB, OUTPUT);
    pinMode(MOTOR_RIGHT_IN3, OUTPUT);
    pinMode(MOTOR_RIGHT_IN4, OUTPUT);
}

void loop() {
    // Check for Bluetooth data
    if (pCharacteristic->getValue()) {
        std::string value = pCharacteristic->getValue();
        // Process received data here
    }
}

void controlMotors(int leftSpeed, int rightSpeed) {
    analogWrite(MOTOR_LEFT_ENA, abs(leftSpeed));
    analogWrite(MOTOR_RIGHT_ENB, abs(rightSpeed));
    digitalWrite(MOTOR_LEFT_IN1, leftSpeed > 0 ? HIGH : LOW);
    digitalWrite(MOTOR_LEFT_IN2, leftSpeed < 0 ? HIGH : LOW);
    digitalWrite(MOTOR_RIGHT_IN3, rightSpeed > 0 ? HIGH : LOW);
    digitalWrite(MOTOR_RIGHT_IN4, rightSpeed < 0 ? HIGH : LOW);
}
