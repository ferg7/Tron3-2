#include <Arduino.h>
#include "hardware/heartbeat.hpp"
#include "door.hpp"

#include "heartbeat.hpp"
#include "wifi.hpp"


Door door;


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); 
  pinMode(buzzer, OUTPUT);
  pinMode(micPin, INPUT);

  //imu_init();

  wifiSetup();

  //knockCalibrate(baselineAcc);
  

  //calibrate();

}


void loop()
{
  heartbeat(500); //used to debug
  door.run();
}
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
  
  char message[200] = {0};
  sendMessage('k');

 
}