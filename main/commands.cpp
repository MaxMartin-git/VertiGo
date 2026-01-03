#include "commands.h"

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