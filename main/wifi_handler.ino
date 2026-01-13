#include "preprocessInput.h"

// wird im main loop aufgerufen

void handleWiFi(WiFiServer &server) {
    WiFiClient client = server.available();
    if (!client) return;

    unsigned long startTime = millis();
    while (!client.available()) {
        if (millis() - startTime > 2000) {
            client.stop();
            Serial.println("Client Timeout");
            return;
        }
        delay(0);
    }

    String req = client.readStringUntil('\r');
    client.flush();

    Serial.print("Request: ");
    Serial.println(req);

    // request nach Fall (Joy/Zustandsbefehl) unterscheiden, entsprechenden handler aufrufen und dort den jeweiligen web-response-typ senden
    
    // Joystick: Sonderfall → kurze Antwort
    if (req.indexOf("GET /joy?") != -1) {
		//if (not manual mode) return zum Vermeiden von Joystickauswertung möglich...aktuell nicht implementiert
        handleJoystickRequest(req, client);   // dort wird kurze Antwort gesendet
        client.stop();
        return; //return, da es nur eine request pro loop gibt und diese damit abgearbeitet ist
    }

    // Zustandsänderungen (einzelne events in größeren Zeitabständen)
    handleStateRequest(req);           // nur Logik ohne HTTP-response

    // Webseite senden
    sendWebpage(client);    //erzeugt Webseiten-Refresh
    client.stop();
}