#include <Arduino.h>
#include "heartbeat.hpp"
#include "imu.hpp"
#include "wifi.hpp"
#include "knock.hpp"

float x, y, z;
float baselineAcc[3] = {0};
boolean knock = false;

//want a watchdog
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);

  imu_init();

  //wifiSetup();

  knockCalibrate(baselineAcc);
  

  //calibrate();

}

void loop()
{
  //heartbeat(500); //used to debug
  //Serial.print("baseline is main ");
  //madgwick();
  //mahony();
  //float x, y, z;
  // readGyro(x, y, z);
  //float results[200] = {0};
  //bufferResults(results, 200);
  //sendMessage('k');
  //writeAcc();
  //detectKnock(baselineAcc);
  knock = detectKnock(baselineAcc);
  if (knock){
    Serial.print('Finish Program');
  }
  

  // sendMessage('k');
  // delay(1000);
}

