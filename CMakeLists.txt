cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)

project(cTensor)
set(cTensor_VERSION_MAJOR 1)
set(cTensor_VERSION_MINOR 0)

set(INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/include)

add_subdirectory(src)
include_directories(include)