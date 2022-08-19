#include "imu.hpp"
#include "SensorFusion.h" //SF
#include <MadgwickAHRS.h>
//#include "kalman.hpp"


SF fusion;
Madgwick filter;
// Kalman kalman;

float gx, gy, gz, ax, ay, az, mx, my, mz;
float pitch, roll, yaw;
float deltat;

float original;

void imu_init(){
    if(!IMU.begin()){
        Serial.println("Failed to initialise");
        return;
    }
    Serial.begin(115200); 
    //filter.begin(1);//altering this helps
    //delay(1000);
}

void readGyro(float x, float y, float z){

    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);

        Serial.print(x);
        Serial.print('\t');
        Serial.print(y);
        Serial.print('\t');
        Serial.println(z);
    }
}

void readAccel(float x, float y, float z){

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

void mahony()
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

    Serial.print("Pitch:\t"); Serial.println(pitch);
    Serial.print("Roll:\t"); Serial.println(roll);
    Serial.print("Yaw:\t"); Serial.println(yaw);
    Serial.println();

}


//Doesn't really work ?  Better when sampling rate changed?
void madgwick(){
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
    }
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gx, gy, gz);
    }

    //may need metro timer 
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    pitch = filter.getPitch();
    roll = filter.getRoll();    //you could also use getRollRadians() ecc
    yaw = filter.getYaw();

    Serial.print("Pitch:\t"); Serial.println(pitch);
    Serial.print("Roll:\t"); Serial.println(roll);
    Serial.print("Yaw:\t"); Serial.println(yaw);
    Serial.println();
}

// void kalman(){

// }