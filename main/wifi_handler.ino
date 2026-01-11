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

    // sinnvoll hier den request nach Fall (Joy/Zustandsbefehl) zu unterscheiden, entsprechenden handler aufrufen und dort den jeweiligen web-response-typ senden?

    Serial.print("Request: ");
    Serial.println(req);

    // --- Logik auslagern ---
    bool sendShortResponse = preprocessInput(req);

    // --- Antwort senden ---
    if (sendShortResponse) {
        client.println("HTTP/1.1 200 OK");
        client.println("Connection: close");
        client.println();
    } else {
        sendWebpage(client); // Standardfall: Webseite senden
    }

    client.stop();
}