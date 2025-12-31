#ifndef CONFIG_H
#define CONFIG_H

// --------------------------------------------------------
//  WLAN-KONFIGURATION
// --------------------------------------------------------
#define WIFI_SSID  "UNO_R4_AP"
#define WIFI_PASS  "12345678"
#define WIFI_PORT     80

// --------------------------------------------------------
//  MOTOR-PINBELEGUNG ??
// --------------------------------------------------------
//#define MOTOR_EN_PIN   9       // Enable-Pin (PWM)
//#define MOTOR_IN1_PIN  7
//#define MOTOR_IN2_PIN  8

// --------------------------------------------------------
//  STARTWERTE //unbenutzt
// --------------------------------------------------------
#define DEFAULT_VELOCITY  120   // Geschwindigkeit nach Start
#define MAX_VELOCITY      255   // Max PWM
#define JOYSTICK_REQUEST_TIME 200

#endif