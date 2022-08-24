#include <Arduino.h>
#include "hardware/heartbeat.hpp"
#include "door.hpp"

Door door;
#include "heartbeat.hpp"
#include "imu.hpp"
#include "wifi.hpp"
#include "knock.hpp"

float x, y, z;
float baselineAcc[3] = {0};
boolean knock = false;
const int buzzer = 2;
const int micPin = 3;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
<<<<<<< HEAD
  Serial.begin(115200); 
<<<<<<< HEAD
  imu_init();
=======
  pinMode(buzzer, OUTPUT);
  pinMode(micPin, INPUT);

  //imu_init();

  wifiSetup();

  //knockCalibrate(baselineAcc);
  

  //calibrate();

>>>>>>> feature/knock
=======
>>>>>>> feature/door-open-detection
}


void loop()
{
<<<<<<< HEAD
  heartbeat(500); //used to debug
  door.run();
}
=======
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

>>>>>>> feature/knock
