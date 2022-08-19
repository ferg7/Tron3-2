#include <Arduino.h>
#include "hardware/heartbeat.hpp""
#include "hardware/imu.hpp"

float x, y, z;
float roll, pitch, yaw;

//want a watchdog
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); 

  imu_init();
}

void loop()
{
  heartbeat(500); //used to debug
  
  //madgwick(&roll, &pitch, &yaw);
  mahony(&roll, &pitch, &yaw);
  
  Serial.print("Pitch:\t"); Serial.println(pitch);
  Serial.print("Roll:\t"); Serial.println(roll);
  Serial.print("Yaw:\t"); Serial.println(yaw);
  Serial.println();

  //can send this data to visualiser.
}

