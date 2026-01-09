#ifndef PREPROCESSINPUT_H
#define PREPROCESSINPUT_H

#include <Arduino.h>  // für String

// Funktionsdeklarationen

// immer im loop aufrufen
bool handleControlRequest(const String &req);

// nur aufrufen, wenn Joystick aktiv sein soll
void handleJoystickRequest(const String &req);

#endif
