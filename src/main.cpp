#include <Arduino.h>
#include "hardware/heartbeat.hpp"
#include "door.hpp"

Door door;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); 
  imu_init();
}


void loop()
{
  heartbeat(500); //used to debug
  door.run();
}