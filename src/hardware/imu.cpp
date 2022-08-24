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
<<<<<<< HEAD:src/hardware/imu.cpp
    float sample_rate = IMU.accelerationSampleRate();
    filter.begin(sample_rate);
    delay(1000);
=======
    Serial.begin(115200); 
    //filter.begin(1);//altering this helps
    //delay(1000);
>>>>>>> feature/knock:src/imu.cpp
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

    //original = sum/10;
    
    //Serial.print("Original ="); Serial.println(original);
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
    float p, r, y;
    p = fusion.getPitch();
    r = fusion.getRoll();    //you could also use getRollRadians() ecc
    y = fusion.getYaw();

    *pitch = p;
    *roll = r;
    *yaw = y;
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

    float p, r, y;
    //returns euler angles in world frame
    p = filter.getPitch();
    r = filter.getRoll();    //you could also use getRollRadians() ecc
    y = filter.getYaw();

    *pitch = p;
    *roll = r;
    *yaw = y;

}
