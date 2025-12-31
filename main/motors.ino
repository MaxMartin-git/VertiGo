#include "config.h"
#include "commands.h"

// Pin-Zuweisungen
const int leftBackward  = 1;
const int leftForward   = 2;
const int leftVelocity  = 3;
const int rightBackward = 4;
const int rightForward  = 5;
const int rightVelocity = 6;

// Pin-Modus setzen
void setMotorpins() {
    pinMode(leftForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(leftVelocity, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(rightBackward, OUTPUT);
    pinMode(rightVelocity, OUTPUT);
}

// Motorsteuerung mit separaten PWM/Richtung
void driveMotors(int leftPWM, int leftDir, int rightPWM, int rightDir) {

    // --- Master-Schalter: Motor generell AUS ---
    if (!enableMotors) {
        digitalWrite(leftForward, LOW);
        digitalWrite(leftBackward, LOW);
        analogWrite(leftVelocity, 0);
        digitalWrite(rightForward, LOW);
        digitalWrite(rightBackward, LOW);
        analogWrite(rightVelocity, 0);
        return;
    }

    // --- Linker Motor ---
    if (leftDir >= 0) {
        digitalWrite(leftForward, HIGH);
        digitalWrite(leftBackward, LOW);
    } else {
        digitalWrite(leftForward, LOW);
        digitalWrite(leftBackward, HIGH);
    }
    analogWrite(leftVelocity, leftPWM);

    // --- Rechter Motor ---
    if (rightDir >= 0) {
        digitalWrite(rightForward, HIGH);
        digitalWrite(rightBackward, LOW);
    } else {
        digitalWrite(rightForward, LOW);
        digitalWrite(rightBackward, HIGH);
    }
    analogWrite(rightVelocity, rightPWM);
}
