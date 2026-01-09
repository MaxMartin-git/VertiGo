#include "preprocessInput.h"
#include "config.h"
#include "commands.h"
unsigned long tts = 0; //zum Testen

bool preprocessInput(const String &req) {
    //RequestResult result = false;

    // === Joystick-Steuerung mit gleichwertiger Skalierung von x und y ===
    if (req.indexOf("GET /joy?") != -1) {
        lastCommandTime = millis();
        int posX = req.indexOf("x=");
        int posY = req.indexOf("y=");
        int posT = req.indexOf("t="); //zum Testen

        if (posX != -1 && posY != -1) { //zur Sicherheit wird geprüft, ob beide Werte vorliegen, um falsche Ansteuerung zu vermeiden
            float fx = req.substring(posX + 2, req.indexOf("&", posX)).toFloat();
            float fy = req.substring(posY + 2, req.indexOf("&", posT)).toFloat();
            unsigned long tts = req.substring(posT + 2).toInt(); //zumTesten

            // Joystick- in Motorwerte umrechnen
            int velocity = round(fy * 125); //255 maxPWM für Arduinoausgänge
            int steering = round(fx * 125);

            int maxLeft  = velocity + steering;
            int maxRight = velocity - steering;

            int maxPWM = max(abs(maxLeft), abs(maxRight));
            if (maxPWM > 255) {
                float scale = 255.0 / maxPWM;
                velocity = round(velocity * scale);
            }

            int tmpLeft  = constrain(velocity + steering, -255, 255);
            int tmpRight = constrain(velocity - steering, -255, 255);

            leftDir  = (tmpLeft >= 0) ? 1 : -1;
            rightDir = (tmpRight >= 0) ? 1 : -1;

            leftPWM  = abs(tmpLeft);
            rightPWM = abs(tmpRight);
        }

        //result.sendShortResponse = true;
        return true;
    }

    // --- Motor EIN ---
    if (req.indexOf("/?motor=on") != -1) {
        enableMotors = true;
        Serial.println("enableMotors: true");
        return false; 
    }

    // --- Motor AUS ---
    if (req.indexOf("/?motor=off") != -1) {
        enableMotors = false;
        Serial.println("enableMotors: false");
        return false; 
    }

    return false; // Standard: Signal für WifiHandler zum Webseite senden, wenn der Request nicht speziell behandelt wird, Webseite laden/ Standardrequests etc.
}
