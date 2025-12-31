#ifndef PREPROCESSINPUT_H
#define PREPROCESSINPUT_H

#include <Arduino.h> // für String

// Struct für die Rückgabe von preprocessInput
struct RequestResult {
    bool sendShortResponse;   // true = nur kurze Text-Antwort (z.B. Joystick)
    String responseText;  // optional: Inhalt der Antwort
};

// Funktionsdeklaration
RequestResult preprocessInput(const String &req);

#endif