cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_C_STANDARD 99)

project(cTensor)
set(cTensor_VERSION_MAJOR 1)
set(cTensor_VERSION_MINOR 0)

set(INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/include)

add_subdirectory(src)
add_subdirectory(app)
include_directories(include)
