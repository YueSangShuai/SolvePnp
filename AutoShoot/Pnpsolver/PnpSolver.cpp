//
// Created by yuesang on 23-2-2.
//

#include "PnpSolver.h"

PNPSolver::PNPSolver() {
    YAML::Node config = YAML::LoadFile("../AutoShoot/Camera/yaml/camera_matrix.yaml");
    auto read_vector = config["Camera_matrix"].as<std::vector<float>>();
    Eigen::MatrixXd mat_intrinsic(3, 3);
    initMatrix(mat_intrinsic,read_vector);


    read_vector= config["Distortion"].as<std::vector<float>>();
    Eigen::MatrixXd mat_dist(1,5);
    initMatrix(mat_dist,read_vector);

//    std::cout<<distortion_coefficients<<std::endl;

}

PNPSolver::~PNPSolver() {

}