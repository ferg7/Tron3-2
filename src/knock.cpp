#include "knock.hpp"
#include "imu.hpp"
#include "imu.hpp"
#include <ctime>

void writeAcc(){
    float x, y, z;
    readAccel(x, y, z);
}

float * bufferResults(float *results, int count){
    float x, y, z;
    for (int i = 0; i < count; i++) {
        IMU.readGyroscope(x, y, z);
        results[i] = x;
        results[i+1] = y;
        results [i+2] = z;
    }  
}


float * knockCalibrate(float *baselineAcc){
    int count = 100;
    float sum_x, sum_y, sum_z = 0;
    float x, y, z;
    for(int i = 0; i < count; i++){
        IMU.readAcceleration(x, y, z);
        sum_x = sum_x + x;
        sum_y = sum_y + y;
        sum_z = sum_z + z;
    }
    baselineAcc[0] =  (sum_x/count);
    baselineAcc[1] =  (sum_y/count);
    baselineAcc[2] =  (sum_z/count);
    //  baselineAcc[0] =  x;
    //  baselineAcc[1] =  y;
    //  baselineAcc[2] =  z;
}

boolean detectVibration(float *baselineAcc){
    
    //detect first knock
    int count = 100;
    float sum_x_dif = 0, sum_y_dif = 0, sum_z_dif = 0;
    float avg_x_dif = 0, avg_y_dif = 0, avg_z_dif=0;
    float x_perc_change = 0,y_perc_change = 0 ,z_perc_change=0;
    float x, y, z;
    boolean sound = 0;

    for(int i = 0; i < count; i++){
        IMU.readAcceleration(x, y, z);
        sum_x_dif = sum_x_dif + abs(baselineAcc[0] - x);
        sum_y_dif = sum_y_dif + abs(baselineAcc[1] - y);
        sum_z_dif = sum_z_dif + abs(baselineAcc[2] - z);
        boolean anySound = digitalRead(3);
        if (anySound){
            sound = 1;   
        }
    }
    

    avg_x_dif = sum_x_dif/count;
    avg_y_dif = sum_y_dif/count;
    avg_z_dif = sum_z_dif/count;


    x_perc_change = abs(avg_x_dif/abs(baselineAcc[0]));
    y_perc_change = abs(avg_y_dif/abs(baselineAcc[1]));
    z_perc_change = abs(avg_z_dif/abs(baselineAcc[2]));

    //Serial.println(x_perc_change);

    if (x_perc_change > 1 and sound == 1){
        return 1;
    }
    else{
        return 0;
    }
}


void doorBell(int buzzer){
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


boolean detectKnock(float *baselineAcc){
    boolean firstKnock =  detectVibration(baselineAcc);
    if (firstKnock){
        long startTime = millis();
        Serial.print("first Knock ");
        delay(50);
        while (millis() - startTime  < 2000){
            boolean secondKnock =  detectVibration(baselineAcc);
            if (secondKnock){
                Serial.println("second knock");
                delay(50);
                return 1;
            }
        }
        return 0;
    }
}

