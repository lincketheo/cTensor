#ifndef NETWORK_TRAIN_HPP
#define NETWORK_TRAIN_HPP

#include <iostream>             //std
#include <vector>               //for training elements
#include <matLib.hpp>           //for matrix propogation
#include <Network.hpp>          //uses network to train
#include <opencv2/opencv.hpp>   //cv::String

namespace training{
    struct trainElem{       //a single training element (only stores  path to file, not actual matrix)
        cv::String file;    //path to file
        int label;          //label for the matrix
    };

    struct trainingSet{
        std::vector<trainElem> files;   //list of file names
        int numIn;                      //number of inputs
        int numOut;                     //number of outputs
        int numTestTypes;               //number of test types (numLabels)
        int numPerType;                 //itterations per  type (numPerLabel)
    };
    
    std::vector<trainElem> uploadImages(int, std::string, std::string, int); //uploads 1 image
    trainingSet uploadAllImages(std::string, const char**, int*, int, std::string, int);
    int getNumIn(cv::String);
    matlib::Matrix createOutput(int, int);
    NetworkLib::Network * trainDataSet(trainingSet, int, int, float);
    bool runOnMatrix(cv::String, NetworkLib::Network*, int);
    float testOnTestSet(trainingSet, NetworkLib::Network*);
}

#endif
