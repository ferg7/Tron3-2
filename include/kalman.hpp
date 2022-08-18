#pragma once

#include <ArduinoEigenDense.h>

using namespace Eigen;

class Kalman {
    public:
        Kalman();
        ~Kalman();
        void init();
        void get_state();
        void run();

    private:
        void predict(float gx, float gy, float gz);
        void update(VectorXd z);

        VectorXd x_prediction, x_estimate;
        MatrixXd P_prediction, P_estimate;

        MatrixXd F, H, B, Q, R;

        VectorXd u, y;

        MatrixXd K_gain, I, Fx;

        int bx, by, bz;


        float dt;
};