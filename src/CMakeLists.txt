cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(cTensor)
set(cTensor_VERSION_MAJOR 1)
set(cTensor_VERSION_MINOR 0)

include_directories(include)

add_subdirectory(   Matrix 
                    Networks)


add_executable(run  main.cpp
                    UI/driver.cpp
                    Matrix/kernel.cpp 
                    Matrix/operations.cpp
                    Networks/Network.cpp)

