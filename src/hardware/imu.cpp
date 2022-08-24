#include "hardware/imu.hpp"
#include <ArduinoEigenDense.h>

IMUclass::IMUclass()
{
    filter = new Madgwick();
    fusion = new SF();

    if(!IMU.begin()){
        Serial.println("Failed to initialise");
        return;
    }
    float sample_rate = IMU.accelerationSampleRate();
    filter->begin(sample_rate);
    delay(1000);
}

IMUclass::~IMUclass()
{

}


void IMUclass::readAccel()
{
    //need to check this
    madgwick();
    Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());

    Eigen::Quaternion<double> q = rollAngle * yawAngle * pitchAngle;

    Eigen::Matrix3d rotationMatrix = q.matrix();

    q.normalize();

    Eigen::Vector3d accel;
    accel << ax, ay, az;
    accel = rotationMatrix*accel; //rotate to World frame

    Eigen::Vector2d planar_accel;
    planar_accel << accel[0], accel[1];
    if(planar_accel.norm() > 1)//needs some thresholding
    {
        //DOOR OPEN
        Serial.println("OPEN");
    }

    //grab the acceleration vector 

}

void IMUclass::calibrate()
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

    deltat = fusion->deltatUpdate(); //this have to be done before calling the fusion update
    //choose only one of these two:
    fusion->MahonyUpdate(gx, gy, gz, ax, ay, az, deltat); 


    float sum = 0;

    for(int i = 0; i < 10; i++){
        fusion->MahonyUpdate(gx, gy, gz, ax, ay, az, deltat);
        sum += fusion->getYaw();
    }

    //original = sum/10;
    
    //Serial.print("Original ="); Serial.println(original);
    delay(10);
    
}


void IMUclass::mahony()
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

    deltat = fusion->deltatUpdate(); //this have to be done before calling the fusion update
    //choose only one of these two:
    fusion->MahonyUpdate(gx, gy, gz, ax, ay, az, deltat);  //mahony is suggested if there isn't the mag and the mcu is slow
    //fusion.MadgwickUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);  //else use the magwick, it is slower but more accurate
    float p, r, y;
    p = fusion->getPitch();
    r = fusion->getRoll();    //you could also use getRollRadians() ecc
    y = fusion->getYaw();

    pitch = p;
    roll = r;
    yaw = y;
    //float current_yaw = yaw;
}


void IMUclass::madgwick()
{
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
    }
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gx, gy, gz);
    }

    //may need metro timer 
    filter->updateIMU(gx, gy, gz, ax, ay, az);

    float p, r, y;
    //returns euler angles in world frame
    p = filter->getPitch();
    r = filter->getRoll();    //you could also use getRollRadians() ecc
    y = filter->getYaw();

    pitch = p;
    roll = r;
    yaw = y;

}
