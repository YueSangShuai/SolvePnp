//
// Created by yuesang on 23-3-31.
//

#include "MyThread.h"

MyThread::MyThread() {
    config=YAML::LoadFile("../AutoShoot/Camera/yaml/camera.yaml");
}

void MyThread::ImageProducter() {
    HaiKang.StartDevice(0);
    // 设置分辨率
    HaiKang.SetResolution(config["ResolutionW"].as<int>(), config["ResolutionH"].as<int>());
    // 开始采集帧
    HaiKang.SetStreamOn();
    // 设置曝光事件
    HaiKang.SetExposureTime(config["ExposureTime"].as<int>());
    //增益设置
//    if(config["setGain"].as<bool>()){
//         HaiKang.SetGAIN(0, 16);
//         HaiKang.SetGAIN(1, 8);
//         HaiKang.SetGAIN(2, 8);
//         HaiKang.SetGAIN(3, 16);
//    }

    // 是否启用自动白平衡7
    if(config["setAutoGain"].as<bool>()){
        HaiKang.Set_Auto_BALANCE();
    }

    // manual白平衡 BGR->012
    if(config["Set_BALANCE"].as<bool>()){
        HaiKang.Set_BALANCE(0, config["B_Gain"].as<int>());
        HaiKang.Set_BALANCE(1, config["G_Gain"].as<int>());
        HaiKang.Set_BALANCE(2, config["R_Gain"].as<int>());
    }


    while(true){
        unique_lock<mutex> lockGuard(muteLock);

        while(!frame.empty()){
            CameraCondition.wait(lockGuard);
        }
        HaiKang.GetMat(frame);
//        cv::imshow("bbb",frame);
//        cv::waitKey(1);
        lockGuard.unlock();
        DetectCondition.notify_all();
    }

}

void MyThread::ImageConsumer() {
    TRTModule model("/home/yuesang/Project/CLionProjects/SolvePnp/AutoShoot/Inference/model/model-opt-3.onnx");
    while(true){
        unique_lock<mutex> lockGuard(muteLock);
        while(frame.empty()){
            DetectCondition.wait(lockGuard);
        }
        model(frame);
        CameraCondition.notify_all();
        frame.release();
        lockGuard.unlock();
    }
}

void MyThread::showPlot() {
    int n = 1000;
    std::vector<double> x, y, z;

    for(int i=0; i<n; i++) {
        x.push_back(i*i);
        y.push_back(sin(2*M_PI*i/360.0));
        z.push_back(log(i));

        if (i % 10 == 0) {
            // Clear previous plot
            plt::clf();
            // Plot line from given x and y data. Color is selected automatically.
            plt::plot(x, y);
            // Plot a line whose name will show up as "log(x)" in the legend.
            plt::named_plot("log(x)", x, z);

            // Set x-axis to interval [0,1000000]
            plt::xlim(0, n*n);

            // Add graph title
            plt::title("Sample figure");
            // Enable legend.
            plt::legend();
            // Display plot continuously
            plt::pause(0.01);
        }
    }
}


