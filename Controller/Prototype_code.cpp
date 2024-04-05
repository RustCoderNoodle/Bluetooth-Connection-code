#include <XBOXONE.h>
#include <SPI.h>
#include <Servo.h> // Include the servo library

USB Usb;
XBOXONE Xbox(&Usb);

// Motor control pins
#define MOTOR_LEFT_ENA 5
#define MOTOR_LEFT_IN1 18
#define MOTOR_LEFT_IN2 19
#define MOTOR_RIGHT_ENB 13
#define MOTOR_RIGHT_IN3 14
#define MOTOR_RIGHT_IN4 27

// Servo control pin for forklift
#define FORKLIFT_SERVO_PIN 4

// Define servo object
Servo forkliftServo;

void setup() {
    Serial.begin(9600);
    if (Usb.Init() == -1) {
        Serial.print(F("\r\nOSC did not start"));
        while (1); //halt
    }
    Serial.print(F("\r\nXBOX USB Library Started"));

    // Initialize motor pins as outputs
    pinMode(MOTOR_LEFT_ENA, OUTPUT);
    pinMode(MOTOR_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_LEFT_IN2, OUTPUT);
    pinMode(MOTOR_RIGHT_ENB, OUTPUT);
    pinMode(MOTOR_RIGHT_IN3, OUTPUT);
    pinMode(MOTOR_RIGHT_IN4, OUTPUT);

    // Attach the servo to the corresponding pin
    forkliftServo.attach(FORKLIFT_SERVO_PIN);
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

        // Map controller inputs to motor speeds
        int leftMotorSpeed = map(LHY, 0, 255, -255, 255);
        int rightMotorSpeed = map(RHY, 0, 255, -255, 255);

        // Control motors based on controller inputs
        analogWrite(MOTOR_LEFT_ENA, abs(leftMotorSpeed));
        analogWrite(MOTOR_RIGHT_ENB, abs(rightMotorSpeed));
        digitalWrite(MOTOR_LEFT_IN1, leftMotorSpeed > 0 ? HIGH : LOW);
        digitalWrite(MOTOR_LEFT_IN2, leftMotorSpeed < 0 ? HIGH : LOW);
        digitalWrite(MOTOR_RIGHT_IN3, rightMotorSpeed > 0 ? HIGH : LOW);
        digitalWrite(MOTOR_RIGHT_IN4, rightMotorSpeed < 0 ? HIGH : LOW);

        // Control forklift mechanism
        if (LA2) {
            forkliftServo.write(90); // Move servo to lift forklift
        } else if (RA2) {
            forkliftServo.write(0); // Move servo to lower forklift
        }

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
