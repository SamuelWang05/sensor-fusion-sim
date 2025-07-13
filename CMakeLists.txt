cmake_minimum_required(VERSION 3.30)
project(autonomous_fusion)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(autonomous_fusion
        src/main.cpp
        src/sensor_data_gen.cpp
        src/sensor_fusion.cpp
        src/output_display.cpp
)