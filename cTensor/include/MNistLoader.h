//
// Created by tjl on 1/17/24.
//

#ifndef CTENSOR_MNISTLOADER_H
#define CTENSOR_MNISTLOADER_H

#include <string>
#include "Matrix.h"
#include "NPZReader.h"

#define XTEST "x_test"
#define XTRAIN "x_train"
#define YTEST "y_test"
#define YTRAIN "y_train"

class MNistLoader {
public:
    explicit MNistLoader(const std::string &filename);

    Matrix xTrainNext();

    Matrix yTrainNext();

    Matrix xTestNext();

    Matrix yTestNext();

    void reset();

    size_t train_l;
    size_t test_l;

    size_t xRows;
    size_t xCols;
    size_t maxY;

private:
    std::vector<uint8_t> xTrain;
    std::vector<uint8_t> xTest;
    std::vector<uint8_t> yTrain;
    std::vector<uint8_t> yTest;

    size_t xTrain_i{0};
    size_t yTrain_i{0};
    size_t xTest_i{0};
    size_t yTest_i{0};

    std::vector<size_t> trainIndices;
};


#endif //CTENSOR_MNISTLOADER_H
