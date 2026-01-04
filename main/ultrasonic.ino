#include "NewPing.h" //functions for ultrasonic
#include "config.h"

// Pin-Zuweisungen
#define trigPin_AR 8
#define echoPin_AR 8
#define trigPin_BR 7
#define echoPin_BR 7
#define max_distance 200 // Maximum distance to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm

NewPing sonar_AR(trigPin_AR, echoPin_AR, max_distance); // NewPing setup of pins and maximum distance.
NewPing sonar_BR(trigPin_BR, echoPin_BR, max_distance);

void US_measure() {

  delay(500); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings
  //unsigned int distance_AR = sonar_AR.ping_cm();
  //unsigned int distance_BR = sonar_BR.ping_cm();

  unsigned int duration_AR = sonar_AR.ping(); //Ultraschall-Zeit hin und zurück in Mikrosekunden
  unsigned int duration_BR = sonar_BR.ping();
  

  Serial.print("value AR = ");
  Serial.print(duration_AR); // Distance will be 0 when out of set max range.
  Serial.print(" microS, value BR = ");
  Serial.print(duration_BR);
  Serial.println(" microS");
}
