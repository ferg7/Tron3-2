#pragma once

#include <Arduino.h>
#include "hardware/imu.hpp"
#include "hardware/ultrasonic.hpp"

float x, y, z;
float roll, pitch, yaw;

unsigned long distance;

void door_init();

void door_open();