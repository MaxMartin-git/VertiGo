#include "config.h"
#include <WiFiS3.h>
#include "commands.h"    // Enthält die Command-Definitionen

WiFiServer server(WIFI_PORT); //Erzeugt einen Webserver auf Port 80 (HTTP)

void setup() {
  Serial.begin(115200); //Aktiviert den Datenstrom zwischen Board ↔ PC (Monitoring in IDE)
  delay(200);

  // Access Point starten
  WiFi.beginAP(WIFI_SSID, WIFI_PASS);
  Serial.print("AP gestartet, IP: ");
  Serial.println(WiFi.localIP());

  server.begin();

  setMotorpins();
}

void loop() {
  handleWiFi(server);   // verarbeitet Anfragen → setzt "command" & "velocity"
  driveMotors(leftPWM, leftDir, rightPWM, rightDir);
}
