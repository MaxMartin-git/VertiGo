#include "commands.h"
//volatile bool uiNeedsRefresh = false;
bool uiNeedsRefresh = false;

int Bewegungsstatus = 0;

void handleSafetyValues(float tilt) {

    //Serial.println(tilt);
    //Kippwinkel
    if ((tilt > 30.0) || (digitalRead(Bewegungsmelder)==HIGH)) { //digitalRead(Bewegungsmelder)
        if (tilt > 30.0){
            enableMotors = false;
            tone(BUZZER, 1000);
            //return;    
        } else {
            tone(BUZZER, 2000);
        }               
    } else {
        noTone(BUZZER);
        digitalWrite(BUZZER, HIGH); //wird mit HIGH ausgeschaltet
    }
    //Serial.println(digitalRead(Bewegungsmelder));
    //noTone(BUZZER);
    //digitalWrite(BUZZER, HIGH); //wird mit HIGH ausgeschaltet
    //Serial.println("Buzzer Off");
}