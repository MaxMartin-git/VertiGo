#ifndef PREPROCESSINPUT_H
#define PREPROCESSINPUT_H

#include <Arduino.h>	// für String
#include <WiFiS3.h>

// Funktionsdeklarationen

void handleStateRequest(const String &req);

void handleJoystickRequest(const String &req, WiFiClient &client);

#endif