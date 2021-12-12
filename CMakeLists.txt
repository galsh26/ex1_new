cmake_minimum_required(VERSION 3.17)
project(ex1)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 HybridAnomalyDetector.cpp HybridAnomalyDetector.h anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h SimpleAnomalyDetector.h timeseries.h timeseries.cpp MainTrain.cpp SimpleAnomalyDetector.cpp minCircle.cpp minCircle.h)