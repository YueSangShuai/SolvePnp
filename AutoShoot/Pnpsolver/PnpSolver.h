//
// Created by yuesang on 23-2-2.
//

#ifndef SOLVEPNP_PNPSOLVER_H
#define SOLVEPNP_PNPSOLVER_H

#include "Eigen/Core"
#include <vector>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "yaml-cpp/yaml.h"
#include "sophus/se3.hpp"

using namespace cv;

class PNPSolver{
private:
    Eigen::Matrix<double ,3,3>  camera_matrix;
    Eigen::Matrix<double ,3,3>  distortion_coefficients;
private:
    template<typename T>
    bool initMatrix(Eigen::MatrixXd &matrix,std::vector<T> &vector)
    {
        int cnt = 0;
        for(int row = 0;row < matrix.rows();row++)
        {
            for(int col = 0;col < matrix.cols();col++)
            {
                matrix(row,col) = vector[cnt];
                cnt++;
            }
        }
        return true;
    }
public:
    PNPSolver();
    ~PNPSolver();


};

#endif //SOLVEPNP_PNPSOLVER_H
