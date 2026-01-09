#ifndef PREPROCESSINPUT_H
#define PREPROCESSINPUT_H

#include <Arduino.h> // für String

// Funktionsdeklaration
bool preprocessInput(const String &req);//RequestResult preprocessInput(const String &req);
extern unsigned long tts; //touchTimeStamp
#endif