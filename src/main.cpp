#include <Arduino.h>
#include "hardware/heartbeat.hpp"
#include "door_open.hpp"


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  door_init();

}

void loop()
{
  heartbeat(500); //used to debug
  door_open();
}