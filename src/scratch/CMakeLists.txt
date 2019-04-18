cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(cTensor)

add_executable(run matrixmain.cpp sparseKernel.cpp)
