 #include "door.hpp"
 

Door::Door()
{

}

Door::~Door()
{
    
}

void Door::run()
{
    door_state();
    
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
    distance = sonar_ping();
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