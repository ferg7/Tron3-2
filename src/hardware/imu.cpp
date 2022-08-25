#include "hardware/imu.hpp"

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
    delay(100);

    Eigen::Vector3d gb, wb;
    gb << 0,0,0;
    wb << 0,0,0;
    g_bias = gb;
    w_bias = wb;

}

IMUclass::~IMUclass()
{

}

void IMUclass::calibrate()
{
    int count = 100;
    double bias_gx = 0, bias_gy = 0, bias_gz = 0;
    double bias_wx = 0, bias_wy = 0, bias_wz = 0;

    for(int i = 0; i < count; i++){
        if (IMU.accelerationAvailable()) {
            IMU.readAcceleration(ax, ay, az);
        }
        if (IMU.gyroscopeAvailable()) {
            IMU.readGyroscope(gx, gy, gz);
        }

        bias_gx += ax;
        bias_gy += ay;
        bias_gz += az;

        bias_wx += gx;
        bias_wy += gy;
        bias_wz += gz;
    }

    g_bias[0] = bias_gx/count;
    g_bias[1] = bias_gy/count;
    g_bias[2] = bias_gz/count;

    w_bias[0] = bias_wx/count;
    w_bias[1] = bias_wy/count;
    w_bias[2] = bias_wz/count;

    g_bias = -1*g_bias;
    w_bias = -1*w_bias;

    diff = 0;

    delay(100);
    Serial.print(g_bias[0]);Serial.print("\t");
    Serial.print(g_bias[1]);Serial.print("\t");
    Serial.print(g_bias[2]);Serial.println();

    Serial.print(w_bias[0]);Serial.print("\t");
    Serial.print(w_bias[1]);Serial.print("\t");
    Serial.print(w_bias[2]);Serial.println();
    
}


float IMUclass::readAccel(Eigen::Vector3d* gb, Eigen::Vector3d* gyr)
{
    //need to check this
    float current_time;

    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
    }
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gx, gy, gz);
    }
    
    current_time = millis();
    
    if(diff == 0){
        diff = 0.01;
    }else{
        diff = current_time - time; //time interval
    }

    time = current_time;

    Eigen::Vector3d acc;

    acc << ax, ay, az;
    *gyr << gx, gy, gz;
    
    acc = acc+g_bias;
    *gyr = *gyr+w_bias;

    *gb << g_bias;

    delay(100);

    //grab the acceleration vector 
    return diff;

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
