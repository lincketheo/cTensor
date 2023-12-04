#ifndef NETWORK_TRAIN_HPP
#define NETWORK_TRAIN_HPP


#include <iostream>             //std
#include <vector>               //for training elements
#include <Matrix.hpp>           //for matrix propogation
#include <Network.hpp>          //uses network to train

struct trainElem {       //a single training element (only stores  path to file, not actual matrix)
    std::string file;    //path to file
    int label;          //label for the matrix
};

struct trainingSet {
    std::vector<trainElem> files;   //list of file names
    int numIn;                      //number of inputs
    int numOut;                     //number of outputs
    int numTestTypes;               //number of test types (numLabels)
    int numPerType;                 //itterations per  type (numPerLabel)
};

std::vector<trainElem> uploadImages(int, const std::string &, const std::string &, int); //uploads 1 image
trainingSet uploadAllImages(const std::string &, const char **, int *, int, const std::string &, int);

int getNumIn(const std::string &);

Matrix createOutput(int, int);

Network *trainDataSet(const trainingSet &, int, int, float);

bool runOnMatrix(const std::string &, Network *, int);

float testOnTestSet(const trainingSet &, Network *);

#endif
