#pragma once

#include <Arduino_LSM6DS3.h>
#include "SensorFusion.h" //SF
#include <MadgwickAHRS.h>
#include <ArduinoEigenDense.h>

class IMUclass
{
    
    public:
        IMUclass();
        ~IMUclass();
        void readAccel(Eigen::Vector3d * accels);

    private:
        
        SF* fusion;
        Madgwick* filter;

        float gx, gy, gz, ax, ay, az;
        float x, y, z;
        float deltat;
        float roll, pitch, yaw;

        void mahony();
        void madgwick();

};