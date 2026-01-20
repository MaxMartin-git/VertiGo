#include "config.h"
#include <WiFiS3.h>
#include "commands.h"
#include "ultrasonic.h"
#include "wallfollow.h"

unsigned long lastIMU = 0;
#define BUZZER  9

WiFiServer server(WIFI_PORT); //Erzeugt einen Webserver auf Port 80 (HTTP)

void setup() {
  Serial.begin(115200); //Aktiviert den Datenstrom zwischen Board ↔ PC (Monitoring in IDE)
  delay(200);

  // Access Point starten
  WiFi.beginAP(WIFI_SSID, WIFI_PASS);
  Serial.print("AP gestartet, IP: ");
  Serial.println(WiFi.localIP());

  server.begin();

  IMU_setup();
  setMotorpins();
}

void loop() { //ab hier wird ständig wiederholt
  static float tilt = 0;
  MotorCmd activeCmd{};

  if (millis() - lastIMU >= 10) {   // 100 Hz
      lastIMU = millis();

      tilt = readIMU();
      //Serial.println(tilt);
  }

  batterieStatus();
  handleWiFi(server);   // handling der requests
  handleSafetyValues(tilt);

  // Fahrmodus abfragen
  if (mode == MANUAL) {
      activeCmd = manualCmd;
  } else {
      US_data us = US_measure();
      activeCmd = wallFollowControl(us);
  }
  
  driveMotors(activeCmd);
}
