//
// Created by tjl on 1/17/24.
//

#include "MNistLoader.h"
#include "NPZReader.h"

MNistLoader::MNistLoader(const std::string &filename) {
    cnpy::npz_t npz = cnpy::npz_load(filename);
    xTest = npz[XTEST];
    xTrain = npz[XTRAIN];
    yTest = npz[YTEST];
    yTrain = npz[YTRAIN];

    // Sizes of vectors
    assert(xTest.shape.size() == 3);
    assert(xTrain.shape.size() == 3);
    assert(yTest.shape.size() == 1);
    assert(yTrain.shape.size() == 1);

    // Same size x / y
    assert(xTrain.shape[0] == yTrain.shape[0]);
    assert(xTest.shape[0] == yTest.shape[0]);

    // X btw train and test have the same size
    assert(xTest.shape[1] == xTrain.shape[1]);
    assert(xTest.shape[2] == xTrain.shape[2]);

    // Raw data arrays are the right size
    assert(xTest.shape[0] * xTest.shape[1] * xTest.shape[2] == xTest.data_holder->size());
    assert(xTrain.shape[0] * xTrain.shape[1] * xTrain.shape[2] == xTrain.data_holder->size());

    xRows = xTrain.shape[1];
    xCols = xTrain.shape[2];
    train_l = xTrain.shape[0];
    test_l = xTest.shape[0];

    maxY = 10;
    for (auto i: *yTrain.data_holder) {
        if ((size_t) i > maxY) {
            maxY = (size_t) (uint8_t) i;
        }
    }
    for (auto i: *yTest.data_holder) {
        if ((size_t) i > maxY) {
            maxY = (size_t) (uint8_t) i;
        }
    }
}

Matrix MNistLoader::xTrainNext() {
    if (xTrain_i >= train_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    char *data = &(*xTrain.data_holder)[xTrain_i * xRows * xCols];
    Matrix ret(xRows * xCols, 1);
    for (int i = 0; i < xRows * xCols; ++i) {
        ret.set(i, 0, ((float) data[i]) / (float) CHAR_MAX);
    }

    xTrain_i++;

    return ret;
}

Matrix MNistLoader::yTrainNext() {
    if (yTrain_i >= train_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    char ind = (*yTrain.data_holder)[yTrain_i];
    Matrix ret(maxY + 1, 1);
    ret.set((size_t) ind, 0, 1.0);

    yTrain_i++;

    return ret;
}

Matrix MNistLoader::xTestNext() {
    if (xTest_i >= test_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    char *data = &(*xTrain.data_holder)[xTest_i * xRows * xCols];
    Matrix ret(xRows * xCols, 1);
    for (int i = 0; i < xRows * xCols; ++i) {
        ret.set(i, 0, ((float) (uint8_t) data[i]));
    }

    xTrain_i++;

    return ret;
}

Matrix MNistLoader::yTestNext() {
    if (yTest_i >= test_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    char ind = (*yTest.data_holder)[yTest_i];
    Matrix ret(maxY + 1, 1);
    ret.set((size_t) ind, 0, 1.0);

    yTest_i++;

    return ret;
}

void MNistLoader::reset() {
    xTrain_i = 0;
    yTrain_i = 0;
    xTest_i = 0;
    yTest_i = 0;
}
