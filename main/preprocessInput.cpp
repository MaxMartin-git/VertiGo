#include "preprocessInput.h"
#include "config.h"
#include "commands.h"


void handleStateRequest(const String &req) {

    // --- Motoren EIN ---
    if (req.indexOf("/?motor=on") != -1) {
        enableMotors = true;
        Serial.println("enableMotors: true");
        return;
    }

    // --- Motoren AUS ---
    if (req.indexOf("/?motor=off") != -1) {
        enableMotors = false;
        Serial.println("enableMotors: false");
		return;
    }
}

void handleJoystickRequest(const String &req, WiFiClient &client) {

    lastCommandTime = millis();

    //Joystick-Steuerung mit gleichwertiger Skalierung von x und y
    int posX = req.indexOf("x=");
    int posY = req.indexOf("y=");

    if (posX == -1 || posY == -1) return; //zur Sicherheit wird geprüft, ob beide Werte vorliegen, um falsche Ansteuerung zu vermeiden

    float fx = req.substring(posX + 2, req.indexOf("&", posX)).toFloat();
    float fy = req.substring(posY + 2).toFloat();

    // Joystick → Motorwerte
    int velocity = round(fy * 125);
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

    leftDir  = (tmpLeft  >= 0) ? 1 : -1;
    rightDir = (tmpRight >= 0) ? 1 : -1;

    leftPWM  = abs(tmpLeft);
    rightPWM = abs(tmpRight);
	
	// send short HTTP-response
	client.println("HTTP/1.1 200 OK");
	client.println("Connection: close");
	client.println();
}