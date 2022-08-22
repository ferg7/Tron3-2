#include "door.hpp"

Door::Door()
{
    pir = new PIR();
}

Door::~Door()
{
    
}

void Door::run()
{
    door_state();
    knock();
    
    Serial.print("Pitch:\t"); Serial.println(pitch);
    Serial.print("Roll:\t"); Serial.println(roll);
    Serial.print("Yaw:\t"); Serial.println(yaw);
    Serial.println();

    //can send this data to visualiser.
    Serial.print("Sonar Distance:\t"); Serial.println(distance);
}

void Door::door_state()
{
    //madgwick(&roll, &pitch, &yaw);
    mahony(&roll, &pitch, &yaw);
    //used for door knock not door open ?

    //add detection of open or clsoed her e
}

void Door::knock()
{
    distance = sonar_ping();
    int motion = pir->run();
    if(motion == 1 && distance < 50)
    {
        //here is where a knock would make sense to exist
    }

    //add imu knock detection here 
}

bool Door::person_detected()
{
    if(distance > 10 && distance < 100)
    {
        return true;
    }else{
        return false;
    }
}