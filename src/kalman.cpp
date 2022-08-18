#include "kalman.hpp"
#include <ArduinoEigenDense.h>

using namespace Eigen;

Kalman::Kalman()
{

}

Kalman::~Kalman()
{

}

void Kalman::init()
{
    MatrixXd Fx = MatrixXd(7,7);
    x_prediction = VectorXd(7);
    x_estimate = VectorXd(7);

    P_prediction = MatrixXd(7,7);
    P_estimate = MatrixXd(7,7);

    F = MatrixXd(7,7); //jacobian 

    dt = 0.01;

    Q = 0.01*(MatrixXd::Identity(7,7));//initial estimate
    
}

void Kalman::run()
{

}

void Kalman::predict(float gx, float gy, float gz)
{
    Fx << 0 -(gx-bx) -(gy-by) -(gz-bz), 0, 0, 0,
        (gx-bx), 0, (gz-bz), -(gy-by), 0, 0, 0,
        (gy-by), -(gz-bz), 0, (gx-bx), 0, 0, 0,
        (gz-bz), (gy-by), -(gx-bx), 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0;
    F = MatrixXd(7,7); //jacobian 
    

    x_prediction = x_estimate+ dt*0.5*Fx*x_estimate;
    P_prediction = F*P_estimate*F.transpose()+Q;
}

void Kalman::update(VectorXd z)
{
    
}