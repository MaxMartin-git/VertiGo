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
        handleJoystickRequest(req, client);
        //send short HTTP-response
        client.println("HTTP/1.1 200 OK");
        client.println("Connection: close");
        client.println();
        client.stop();
        return; //return, da es nur eine request pro loop gibt und diese damit abgearbeitet ist
    }
    else if (req.indexOf("GET /favicon.ico") >= 0) {
        client.println("HTTP/1.1 204 No Content");
        client.println("Connection: close");
        client.println();
        client.stop();
        return;
    }

    // Zustandsänderungen (einzelne events in größeren Zeitabständen)
    if (handleStateRequest(req, client)) {
        client.println("HTTP/1.1 303 See Other");
        client.println("Location: /");
        client.println("Connection: close");
        client.println();
        client.stop();
        Serial.println("Erster Req-Durchlauf");
        return;  // Antwort ist fertig (redirect), wenn im ersten Durchlauf auf true gesetzt wird
    }            // sonst -> Webseite senden

    // Webseite senden
    sendWebpage(client);    //erzeugt Webseiten-Refresh
    client.stop();
}