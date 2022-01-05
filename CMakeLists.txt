cmake_minimum_required(VERSION 3.17)
project(ex1)

find_package(Threads REQUIRED)

target_link_libraries(${ex1} Threads::Threads)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3 HybridAnomalyDetector.cpp HybridAnomalyDetector.h anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h SimpleAnomalyDetector.h timeseries.h timeseries.cpp MainTrain.cpp SimpleAnomalyDetector.cpp minCircle.cpp minCircle.h CLI.cpp CLI.h commands.h Server.cpp Server.h)