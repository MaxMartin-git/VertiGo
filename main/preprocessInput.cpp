#include "preprocessInput.h"
#include "config.h"
#include "commands.h"

RequestResult preprocessInput(const String &req) {
    RequestResult result = {false, ""};

    // ===Joystick-Steuerung mit Lenkungs-Priorität ===
    if (req.indexOf("GET /joy?") != -1) {
        lastCommandTime = millis();
        int posX = req.indexOf("x=");
        int posY = req.indexOf("y=");

        if (posX != -1 && posY != -1) {
            float fx = req.substring(posX + 2, req.indexOf("&", posX)).toFloat();
            float fy = req.substring(posY + 2).toFloat();

            // Joystick in Motorwerte umrechnen
            velocity = round(fy * 255);
            steering = round(fx * 255);

            // Wenn Joystick auf null → Motor stoppen - funktioniert noch nicht (stoppt nicht automatisch)
            if (velocity == 0 && steering == 0) {
                leftPWM = 0;
                rightPWM = 0;
                leftDir = 1;   // egal, Hauptsache kein Strom
                rightDir = 1;
            } else {
                // normale Berechnung mit Lenkung
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
        } // <-- Ende if posX/posY gefunden

        result.sendShortResponse = true;
        result.responseText = "OK";
        return result;
    }

    // --- Motor EIN ---
    if (req.indexOf("/?motor=on") != -1) {
        enableMotors = true;
        Serial.println("enableMotors: true");
        return result; 
    }

    // --- Motor AUS ---
    if (req.indexOf("/?motor=off") != -1) {
        enableMotors = false;
        Serial.println("enableMotors: false");
        return result; 
    }

    return result; // Standard: Webseite senden
}
