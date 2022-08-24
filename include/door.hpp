#pragma once

#include <Arduino.h>
#include "hardware/imu.hpp"
#include "hardware/ultrasonic.hpp"
#include "hardware/pir.hpp"



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

        float baslineX, baslineY, BaselineZ;

        unsigned long distance;

        PIR *pir;
        IMUclass* imu;

        void door_state();
        void knock();
        void knockCalibrate();
        void doorBell();
};
