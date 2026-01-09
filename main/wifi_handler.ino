#include "preprocessInput.h"

void handleWiFi(WiFiServer &server) {
    unsigned long tClient = millis();
    WiFiClient client = server.available();
    if (!client) return;

    unsigned long startTime = millis();
    while (!client.available()) {
        if (millis() - startTime > 2000) {
            client.stop();
            Serial.println("Client Timeout");
            return;
        }
        delay(1);
    }

    unsigned long tAvailable = millis();

    String req = client.readStringUntil('\r');
    client.flush();

    unsigned long tReadDone = millis();
//-------------Test---------------------------------
    Serial.print("waitForClient: ");
    Serial.println(startTime - tClient);

    Serial.print("waitForData: ");
    Serial.println(tAvailable - startTime);

    Serial.print("readString: ");
    Serial.println(tReadDone - tAvailable);
//---------------------------------------------------
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
        // Standardfall: Webseite senden
        sendWebpage(client);
    }

    client.stop();
}