#include <Arduino.h>
#include "heartbeat.hpp"
#include "imu.hpp"
#include "wifi.hpp"
#include "knock.hpp"

float x, y, z;
float baselineAcc[3] = {0};
boolean knock = false;
const int buzzer = 2;
const int micPin = 3;

//want a watchdog
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(micPin, INPUT);

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
  // sendMessage('k');
  //writeAcc();
  
  knock = detectKnock(baselineAcc);
  if (knock){
    Serial.print("Finish Program");
    doorBell(buzzer);
    doorBell(buzzer);
    doorBell(buzzer);
  }
  

  // sendMessage('k');
 
}

