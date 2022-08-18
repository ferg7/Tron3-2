#pragma once

#include <Arduino_LSM6DS3.h>

void imu_init();

void readGyro(float x, float y, float z);

void readAccel(float x, float y, float z);

void mahony();

void madgwick();

void calibrate();