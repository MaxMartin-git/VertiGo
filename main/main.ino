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

void loop() { //ab hier wird ständig wiederholt
  MotorCmd activeCmd;
  handleWiFi(server);   // handling der requests

  // Fahrmodus abfragen
  if (mode == MANUAL) {
      activeCmd = manualCmd;
  } else {
      activeCmd = autoCmd;
  }

  driveMotors(activeCmd);
  //US_measure();
}
