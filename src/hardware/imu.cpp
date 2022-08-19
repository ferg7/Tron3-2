#include "hardware/imu.hpp"
#include "SensorFusion.h" //SF
#include <MadgwickAHRS.h>
//#include "kalman.hpp"

SF fusion;
Madgwick filter;

float gx, gy, gz, ax, ay, az;
float x, y, z;
float deltat;

void imu_init()
{
    if(!IMU.begin()){
        Serial.println("Failed to initialise");
        return;
    }
    float sample_rate = IMU.accelerationSampleRate();
    filter.begin(sample_rate);
    delay(1000);
}

void readGyro()
{
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);

        Serial.print(x);
        Serial.print('\t');
        Serial.print(y);
        Serial.print('\t');
        Serial.println(z);
    }
}

void readAccel()
{
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);

        Serial.print(x);
        Serial.print('\t');
        Serial.print(y);
        Serial.print('\t');
        Serial.println(z);
    }
}

void calibrate()
{
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
    }
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gx, gy, gz);
    }

    gx = gx*DEG_TO_RAD;
    gy = gy*DEG_TO_RAD;
    gz = gz*DEG_TO_RAD;

    deltat = fusion.deltatUpdate(); //this have to be done before calling the fusion update
    //choose only one of these two:
    fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, deltat); 


    float sum = 0;

    for(int i = 0; i < 10; i++){
        fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, deltat);
        sum += fusion.getYaw();
    }

    original = sum/10;
    
    Serial.print("Original ="); Serial.println(original);
    delay(10);
    
}


void mahony(float *roll, float *pitch, float *yaw)
{
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
    }
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gx, gy, gz);
    }

    gx = gx*DEG_TO_RAD;
    gy = gy*DEG_TO_RAD;
    gz = gz*DEG_TO_RAD;

    deltat = fusion.deltatUpdate(); //this have to be done before calling the fusion update
    //choose only one of these two:
    fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, deltat);  //mahony is suggested if there isn't the mag and the mcu is slow
    //fusion.MadgwickUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);  //else use the magwick, it is slower but more accurate

    pitch = fusion.getPitch();
    roll = fusion.getRoll();    //you could also use getRollRadians() ecc
    yaw = fusion.getYaw();
    //float current_yaw = yaw;
}


void madgwick(float *roll, float *pitch, float *yaw)
{
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
    }
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gx, gy, gz);
    }

    //may need metro timer 
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    //returns euler angles in world frame
    pitch = filter.getPitch();
    roll = filter.getRoll();    //you could also use getRollRadians() ecc
    yaw = filter.getYaw();

}
