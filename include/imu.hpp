#pragma once

#include <Arduino_LSM6DS3.h>

void imu_init();

void readGyro();

void readAccel();

void mahony(float *roll, float *pitch, float *yaw);

void madgwick(float *roll, float *pitch, float *yaw);

void calibrate();