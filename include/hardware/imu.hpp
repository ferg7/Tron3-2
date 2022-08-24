#pragma once

#include <Arduino_LSM6DS3.h>
#include "SensorFusion.h" //SF
#include <MadgwickAHRS.h>

class IMUclass
{
    
    public:
        IMUclass();
        ~IMUclass();
        void readAccel();
        void mahony();
        void madgwick();


    private:
        void calibrate();   
        
        SF* fusion;
        Madgwick* filter;

        float gx, gy, gz, ax, ay, az;
        float x, y, z;
        float deltat;
        float roll, pitch, yaw;

};