//
// Created by yuesang on 23-3-31.
//

#ifndef SOLVEPNP_MYTHREAD_H
#define SOLVEPNP_MYTHREAD_H

#include "../AutoShoot/Camera/HaikangCamera/CameraRGB/HaiKangCameraRGB.h"
#include "yaml-cpp/yaml.h"
#include <thread>
#include <condition_variable>
#include "../AutoShoot/Inference/TRT/TRTModule.h"
#include "../matplotlibcpp.h"

namespace plt = matplotlibcpp;

class MyThread {
public:
    // 无参数构造函数
    MyThread();

    // 获取图像函数
    void ImageProducter();

    // 图像处理函数
    void ImageConsumer();

    //显示波形函数
    void showPlot();

private:
    HaiKangCameraRGB HaiKang;
    YAML::Node config;
    condition_variable CameraCondition,DetectCondition;
    mutex muteLock;
    cv::Mat frame;

    std::vector<double> tx,ty,tz;
};

#endif //SOLVEPNP_MYTHREAD_H
