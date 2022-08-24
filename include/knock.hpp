#include <Arduino_LSM6DS3.h>

void writeAcc();

float * bufferResults(float *results, int count);

float * knockCalibrate(float *baselineAcc);

boolean detectVibration(float * baselineAcc);

boolean detectMic();

boolean detectKnock(float * baselineAcc);

void doorBell(int buzzer);