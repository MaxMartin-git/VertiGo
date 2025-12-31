#include "commands.h"

// Geschwindigkeit / Lenkung
int velocity = 0;
int steering = 0;

// PWM-Werte für die Motoren
int leftPWM = 0;
int rightPWM = 0;

// Richtung der Motoren
int leftDir = 1;
int rightDir = 1;

// Motoren aktiviert oder deaktiviert
bool enableMotors = false;

//timestamp des letzten Kommandos
unsigned long lastCommandTime = 0;