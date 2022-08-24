#include <Arduino.h>
#include "hardware/pir.hpp"

int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

PIR::PIR() 
{
  pinMode(sensor, INPUT);    // initialize sensor as an input
    state = LOW;
}

PIR::~PIR()
{

}

int PIR::run(){
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    //on
    delay(100);                // delay 100 milliseconds 

    if (state == LOW) {
      //Motion detected!
      state = HIGH;
      return 1;
    }
  } 
  else {
      delay(200);             // delay 200 milliseconds 
      if (state == HIGH){
        //Motion stopped
        state = LOW;       // update variable state to LOW
        return 0;
    }
  }
}