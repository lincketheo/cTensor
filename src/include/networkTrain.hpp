#ifndef NETWORK_TRAIN_HPP
#define NETWORK_TRAIN_HPP

#include <iostream>
#include <vector>
#include <matLib.hpp>
#include <Network.hpp>
#include <opencv2/opencv.hpp>

namespace training{
    struct trainElem{
        cv::String file;
        int label;
    };

    struct trainingSet{
        std::vector<trainElem> files;
        int numIn;
        int numOut;
        int numTestTypes;
        int numPerType;
    };
    
    std::vector<trainElem> uploadImages(int, std::string, std::string, int);
    trainingSet uploadAllImages(std::string, const char**, int*, int, std::string, int);
    int getNumIn(cv::String);
    matlib::Matrix createOutput(int, int);
    NetworkLib::Network trainDataSet(trainingSet, int, int, float);
    bool runOnMatrix(cv::String, NetworkLib::Network&, int);
    float testOnTestSet(trainingSet, NetworkLib::Network&);
    //float testNetworkOnImage(Network, int, std::string);
}

#endif
