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
        float readAccel(Eigen::Vector3d* g_bias, Eigen::Vector3d* gyr);
        void calibrate();

    private:
        
        SF* fusion;
        Madgwick* filter;

        float gx, gy, gz, ax, ay, az;
        float x, y, z;
        float deltat;
        float roll, pitch, yaw;

        Eigen::Vector3d g_bias;
        Eigen::Vector3d w_bias;

        void mahony();
        void madgwick();

        float time, diff;


};