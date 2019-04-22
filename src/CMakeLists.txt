cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)

project(cTensor)
set(cTensor_VERSION_MAJOR 1)
set(cTensor_VERSION_MINOR 0)

find_package( OpenCV REQUIRED )

include_directories(../include)

add_subdirectory(   Matrix 
                    Networks)


add_executable(runTheDamnNetwork
                    runTheDamnNetwork.cpp
                    UI/driver.cpp
                    Matrix/kernel.cpp 
                    Matrix/operations.cpp
                    Networks/Network.cpp
                    Data/dataHandler.cpp)

add_executable(run  main.cpp
                    UI/driver.cpp
                    Matrix/kernel.cpp
                    Matrix/operations.cpp
                    Networks/Network.cpp
                    Data/dataHandler.cpp)

target_link_libraries( runTheDamnNetwork ${OpenCV_LIBS})
target_link_libraries( run ${OpenCV_LIBS} )

