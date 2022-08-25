#include <Arduino.h>
#include "hardware/heartbeat.hpp"
#include "door.hpp"
//#include "wifi.hpp"

Door* door = NULL;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 

  door = new Door();
  

  //wifiSetup();

  //knockCalibrate(baselineAcc);
  

  //calibrate();

}


void loop()
{
  //heartbeat(500); //used to debug
  door->run();

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
  
  // knock = detectKnock(baselineAcc);
  // if (knock){
  //   Serial.print("Finish Program");
  //   doorBell(buzzer);
  //   doorBell(buzzer);
  //   doorBell(buzzer);
  // }
  
  //char message[200] = {0};
  //sendMessage('k');

 
}