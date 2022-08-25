#pragma once

#include <Arduino.h>
#include "hardware/imu.hpp"
//#include "hardware/ultrasonic.hpp"
//#include "hardware/pir.hpp"



class Door
{
    public:
        Door();
        ~Door();
        void run();
        bool person_detected();
        bool open(); //true for open, false for closed

    private:
        float roll, pitch, yaw;

        int buzzer, micPin;

        float baselineX, baselineY, baselineZ;

        unsigned long distance;

        //PIR *pir;
        IMUclass* imu = NULL;


        void door_state();
        boolean knock();
        void knockCalibrate();
        boolean detectVibration();
        void doorBell();

        bool closed;
        
        int dir_to_open;
};
