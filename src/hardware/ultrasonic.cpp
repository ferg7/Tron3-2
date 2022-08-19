#include "hardware/ultrasonic.hpp"

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

const int lowDist = 10;

unsigned long sonar_ping()
{
    if(sonar.ping_cm() >= lowDist || sonar.ping_cm() == 0)
    {
        //valid result 
        return sonar.ping_cm();
    }
    delay(50);
}
