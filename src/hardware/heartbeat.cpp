#include "hardware/heartbeat.hpp"

void heartbeat(int seconds){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(seconds);
  digitalWrite(LED_BUILTIN, LOW);
  delay(seconds);
}