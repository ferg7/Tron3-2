#include "door.hpp"

Door::Door()
{
    pir = new PIR();
    imu = new IMUclass();
    knockCalibrate();

    buzzer = 2;
    micPin = 3;

}

Door::~Door()
{
    delete pir;
    delete imu;
}

void Door::run()
{
    //imu->madgwick();
    door_state();
    knock();
    
    //required for the visualiser
    Serial.print("Pitch:\t"); Serial.println(pitch);
    Serial.print("Roll:\t"); Serial.println(roll);
    Serial.print("Yaw:\t"); Serial.println(yaw);
    Serial.println();

    //can send this data to visualiser.
    Serial.print("Sonar Distance:\t"); Serial.println(distance);
}

void Door::door_state()
{
    
}

void Door::knock()
{
    boolean firstKnock =  detectVibration();
    if (firstKnock){
        long startTime = millis();
        Serial.print("first Knock ");
        delay(50);
        while (millis() - startTime  < 2000){
            boolean secondKnock =  detectVibration();
            if (secondKnock){
                Serial.println("second knock");
                delay(50);
                return 1;
            }
        }
        return 0;
    }


    // distance = sonar_ping();
    // int motion = pir->run();
    // if(motion == 1 && distance < 50)
    // {
    //     //here is where a knock would make sense to exist
    // }

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

void Door::knockCalibrate(){
    int count = 100;
    float sum_x, sum_y, sum_z = 0;
    float x, y, z;
    for(int i = 0; i < count; i++){
        IMU.readAcceleration(x, y, z);
        sum_x = sum_x + x;
        sum_y = sum_y + y;
        sum_z = sum_z + z;
    }
    baselineX =  (sum_x/count);
    baselineY =  (sum_y/count);
    baselineZ =  (sum_z/count);
}


void Door::doorBell(){
    tone(buzzer, 330); // tone(PIN#, FREQUENCY)
    delay(400);
    tone(buzzer, 390);
    delay(400);
    tone(buzzer, 260);
    delay(400);
    noTone(buzzer);
    delay(1000);
    //https://www.npsmusicsound.com/hybridcomputermusic/an-easy-door-bell-with-arduino-uno
}

boolean Door::detectVibration(){
    
    //detect first knock
    int count = 100;
    float sum_x_dif = 0, sum_y_dif = 0, sum_z_dif = 0;
    float avg_x_dif = 0, avg_y_dif = 0, avg_z_dif=0;
    float x_perc_change = 0,y_perc_change = 0 ,z_perc_change=0;
    float x, y, z;
    boolean sound = 0;

    for(int i = 0; i < count; i++){
        IMU.readAcceleration(x, y, z);
        sum_x_dif = sum_x_dif + abs(baselineX - x);
        sum_y_dif = sum_y_dif + abs(baselineY - y);
        sum_z_dif = sum_z_dif + abs(baselineZ - z);
        boolean anySound = digitalRead(3);
        if (anySound){
            sound = 1;   
        }
    }
    

    avg_x_dif = sum_x_dif/count;
    avg_y_dif = sum_y_dif/count;
    avg_z_dif = sum_z_dif/count;


    x_perc_change = abs(avg_x_dif/abs(baselineX));
    y_perc_change = abs(avg_y_dif/abs(baselineY));
    z_perc_change = abs(avg_z_dif/abs(baselineZ));

    //Serial.println(x_perc_change);

    if (x_perc_change > 1 and sound == 1){
        return 1;
    }
    else{
        return 0;
    }
}