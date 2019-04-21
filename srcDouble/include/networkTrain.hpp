#ifndef NETWORK_TRAIN_HPP
#define NETWORK_TRAIN_HPP

#include <iostream>
#include <vector>
#include <matLib.hpp>
#include <Network.hpp>

namespace training{
    struct testElement{
        matlib::Matrix mat;
        int label;
    };
    
    std::vector<testElement> uploadImages(int, std::string, std::string, int);
    std::vector<testElement> uploadAllImages(std::string, const char**, int*, int, std::string, int);
    int getNumOut(std::vector<testElement>);
    int getNumIn(std::vector<testElement>);
    matlib::Matrix createOutput(int, int);
    NetworkLib::Network trainDataSet(std::vector<testElement>, int, int, float);
    void runOnMatrix(NetworkLib::Network, matlib::Matrix, int);
    
    //float testNetworkOnImage(Network, int, std::string);
}

#endif
