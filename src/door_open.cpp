 #include "door_open.hpp"
 
void door_init()
{
    Serial.begin(115200); 
    imu_init();
}

void door_open()
{
    //madgwick(&roll, &pitch, &yaw);
    mahony(&roll, &pitch, &yaw);

    Serial.print("Pitch:\t"); Serial.println(pitch);
    Serial.print("Roll:\t"); Serial.println(roll);
    Serial.print("Yaw:\t"); Serial.println(yaw);
    Serial.println();
    //can send this data to visualiser.

    distance = sonar_ping();
    Serial.print("Sonar Distance:\t"); Serial.println(distance);
}