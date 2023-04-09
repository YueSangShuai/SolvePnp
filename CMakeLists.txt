cmake_minimum_required(VERSION 3.23)
project(SolvePnp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(CUDA)
find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Ceres REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)

find_package(PythonLibs 3.9 REQUIRED)
find_package(matplotlib_cpp REQUIRED)

find_package(Qt5 COMPONENTS Core  Widgets PrintSupport REQUIRED)

set(TENSORRT_PATH /home/yuesang/include//TensorRT-release-8.4/)
set(TENSORRT_LIB_PATH /home/yuesang/include/TensorRT-release-8.4/lib)

include_directories(${OpenCV_INCLUDE_DIRS}) #加这一句
include_directories(${TENSORRT_PATH}/include) #加这一句
include_directories(${CUDA_INCLUDE_DIRS}) #加这一句
include_directories(${Fmt_INCLUDE_DIRS}) #加这一句
include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${Sophus_INCLUDE_DIRS})

set(SOURCE_FILES
        main.cpp
        AutoShoot/Inference/Logger/Logger.h
        AutoShoot/Inference/TRT/TRTModule.h
        AutoShoot/Inference/TRT/TRTModule.cpp

        AutoShoot/Camera/HaikangCamera/CameraRGB/HaiKangCameraRGB.cpp
        AutoShoot/Camera/HaikangCamera/CameraRGB/HaiKangCameraRGB.h
        AutoShoot/Camera/HaikangCamera/CameraGray/HaiKangCameraGray.cpp
        AutoShoot/Camera/HaikangCamera/CameraGray/HaiKangCameraGray.h

        AutoShoot/Kalma/KF/kf_cv_one.cpp
        AutoShoot/Kalma/KF/kf_cv_one.h
        AutoShoot/Kalma/KF/kf_ca_one.cpp
        AutoShoot/Kalma/KF/kf_ca_one.h

        AutoShoot/Kalma/EKF/ekf_cv_one.cpp
        AutoShoot/Kalma/EKF/ekf_cv_one.h
        AutoShoot/Kalma/KF/kf_cv_three.cpp
        AutoShoot/Kalma/KF/kf_cv_three.h
        AutoShoot/Kalma/EKF/ekf_cv_aw.cpp
        AutoShoot/Kalma/EKF/ekf_cv_aw.h
        AutoShoot/Kalma/EKF/ekf_cv_awb.cpp
        AutoShoot/Kalma/EKF/ekf_cv_awb.h

        AutoShoot/Kalma/Buff/Buffpredict.cpp
        AutoShoot/Kalma/Buff/Buffpredict.h
        AutoShoot/Kalma/Buff/kffilter.cpp
        AutoShoot/Kalma/Buff/kffilter.h
        AutoShoot/Pnpsolver/PnpSolver.cpp
        AutoShoot/Pnpsolver/PnpSolver.h
        Thread/MyThread.cpp
        Thread/MyThread.h
        )
file(GLOB TENSORRT_LIBS "${TENSORRT_LIB_PATH}/*.so")#添加这句


# 包含海康相机动态链接库
find_library(MVS_LIB libMvCameraControl.so /opt/MVS/lib/64/)
cuda_add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MVS_LIB}
        ${OpenCV_LIBS}
        ${TENSORRT_LIBS}
        ${CUDA_LIBRARIES}
        ${CERES_LIBRARIES}
        cuda
        fmt
        nvinfer
        nvonnxparser
        yaml-cpp
        matplotlib_cpp::matplotlib_cpp
        )

