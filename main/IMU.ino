#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t ax_raw, ay_raw, az_raw;

void IMU_setup() {
  
    Wire.begin();
    mpu.initialize();

    if (!mpu.testConnection()) {
        Serial.println("MPU6050 nicht erreichbar!");
        while (1);
    }

    Serial.println("MPU6050 bereit");
}

float readIMU() {
    mpu.getAcceleration(&ax_raw, &ay_raw, &az_raw);
    
    float ax = ax_raw / 16384.0;
    float ay = ay_raw / 16384.0;
    float az = az_raw / 16384.0;

    float a = sqrt(ax*ax + ay*ay + az*az); //a = g ohne zusaätzliche Beschleunigung
    float cosTilt = az / a;

    cosTilt = constrain(cosTilt, -1.0, 1.0);

    float tilt = acos(cosTilt) * 180.0 / PI;
    /*
    Serial.print("Tilt: ");
    Serial.print(tilt);
    Serial.println(" Grad");
    */
    return tilt;
}
