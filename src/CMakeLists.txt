cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(cTensor)
set(cTensor_VERSION_MAJOR 1)
set(cTensor_VERSION_MINOR 0)

include_directories(
    ../include/
	) 
add_subdirectory(
	linearAlg/noGPU
        NeuralNetwork
)


add_executable(run NeuralNetwork/network.cpp
		main.cpp
		linearAlg/noGPU/tensor.cpp)

