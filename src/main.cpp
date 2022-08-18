#include <Arduino.h>
#include "heartbeat.hpp"
#include "imu.hpp"

float x, y, z;

//want a watchdog
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);

  imu_init();

  //calibrate();

}

void loop()
{
  heartbeat(500); //used to debug
  //madgwick();
  //mahony();
  float x, y, z;
  readGyro(x, y, z);
}

