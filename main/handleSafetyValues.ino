#include "commands.h"
//volatile bool uiNeedsRefresh = false;
bool uiNeedsRefresh = false;

void handleSafetyValues(float tilt) {
    //Serial.println(tilt);
    //Kippwinkel
    if (tilt > 30.0) {
        enableMotors = false;
        tone(BUZZER, 1000);
        return;                   
    }
    
    noTone(BUZZER);
    digitalWrite(BUZZER, HIGH); //wird mit HIGH ausgeschaltet
    //Serial.println("Buzzer Off");
}

//Probleme: IMU manchmal nicht erreichbar/ liefert keine neuen Werte und Webseite updatet Antriebsfreigabe nicht