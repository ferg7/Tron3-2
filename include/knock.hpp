#include <Arduino_LSM6DS3.h>

void writeAcc();

float * bufferResults(float *results, int count);

float * knockCalibrate(float *baselineAcc);

boolean detectKnockVibration(float * baselineAcc);

boolean detectKnock(float * baselineAcc);