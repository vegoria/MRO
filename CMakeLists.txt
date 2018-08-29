cmake_minimum_required(VERSION 3.12)
project(MRO)

set(CMAKE_CXX_STANDARD 17)

add_executable(MRO main.cpp tgaSrc/TPGM.h tgaSrc/TPGM.cpp include/imageManagment.hpp source/imageManagment.cpp include/imageOperations.hpp source/imageOperations.cpp)