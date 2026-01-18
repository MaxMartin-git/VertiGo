#include "commands.h"

void handleSafetyValues(float tilt) {
    //Serial.println(tilt);
    //Kippwinkel
    if (tilt > 30.0) {
        //enableMotors = false; //Fahrbeschleunigung führt noch zum Auslösen - evtl. Reaktion träger machen/ Messung filtern
        //digitalWrite(LED_ERROR, HIGH);
        tone(BUZZER, 1000);
        //digitalWrite(BUZZER, LOW);
        return;                   
    }
    
    noTone(BUZZER);
    digitalWrite(BUZZER, HIGH); //wird mit HIGH ausgeschaltet
    Serial.println("Buzzer Of");
}