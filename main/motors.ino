#include "config.h"
#include "commands.h"

// Pin-Zuweisungen
#define leftBackward  1
#define leftForward   2
#define leftVelocity  3
#define rightBackward 4
#define rightForward  5
#define rightVelocity 6

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
void driveMotors(const MotorCmd &cmd) {

    // --- Master-Schalter: Motor generell AUS ---
    if (!enableMotors) {
        digitalWrite(leftForward, LOW);
        digitalWrite(leftBackward, LOW);
        digitalWrite(rightForward, LOW);
        digitalWrite(rightBackward, LOW);
        return;
    }

    // --- Linker Motor ---
    if (cmd.leftDir >= 0) {
        digitalWrite(leftForward, HIGH);
        digitalWrite(leftBackward, LOW);
    } else {
        digitalWrite(leftForward, LOW);
        digitalWrite(leftBackward, HIGH);
    }
    analogWrite(leftVelocity, cmd.leftPWM);

    // --- Rechter Motor ---
    if (cmd.rightDir >= 0) {
        digitalWrite(rightForward, HIGH);
        digitalWrite(rightBackward, LOW);
    } else {
        digitalWrite(rightForward, LOW);
        digitalWrite(rightBackward, HIGH);
    }
    analogWrite(rightVelocity, cmd.rightPWM);
}
