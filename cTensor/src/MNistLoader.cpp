//
// Created by tjl on 1/17/24.
//

#include <algorithm>
#include <random>
#include "MNistLoader.h"
#include "NPZReader.h"

MNistLoader::MNistLoader(const std::string &filename) {
    cnpy::npz_t npz = cnpy::npz_load(filename);
    cnpy::NpyArray _xTest = npz[XTEST];
    cnpy::NpyArray _xTrain = npz[XTRAIN];
    cnpy::NpyArray _yTest = npz[YTEST];
    cnpy::NpyArray _yTrain = npz[YTRAIN];

    // Sizes of vectors
    assert(_xTest.shape.size() == 3);
    assert(_xTrain.shape.size() == 3);
    assert(_yTest.shape.size() == 1);
    assert(_yTrain.shape.size() == 1);

    // Same size x / y
    assert(_xTrain.shape[0] == _yTrain.shape[0]);
    assert(_xTest.shape[0] == _yTest.shape[0]);

    // X btw train and test have the same size
    assert(_xTest.shape[1] == _xTrain.shape[1]);
    assert(_xTest.shape[2] == _xTrain.shape[2]);

    // Raw data arrays are the right size
    assert(_xTest.shape[0] * _xTest.shape[1] * _xTest.shape[2] == _xTest.data_holder->size());
    assert(_xTrain.shape[0] * _xTrain.shape[1] * _xTrain.shape[2] == _xTrain.data_holder->size());

    xRows = _xTrain.shape[1];
    xCols = _xTrain.shape[2];
    train_l = _xTrain.shape[0];
    test_l = _xTest.shape[0];

    maxY = 0;
    xTrain = _xTrain.as_vec<uint8_t>();
    xTest = _xTest.as_vec<uint8_t>();
    yTrain = _yTrain.as_vec<uint8_t>();
    yTest = _yTest.as_vec<uint8_t>();

    for (auto i: yTrain) {
        if ((size_t) i > maxY) {
            maxY = (size_t) (uint8_t) i;
        }
    }
    for (auto i: yTest) {
        if ((size_t) i > maxY) {
            maxY = (size_t) (uint8_t) i;
        }
    }

    trainIndices = std::vector<size_t>(train_l);
    std::iota(trainIndices.begin(), trainIndices.end(), 0);

    reset();
}

Matrix MNistLoader::xTrainNext() {
    if (xTrain_i >= train_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    Matrix ret(xRows * xCols, 1);
    for (int i = 0; i < xRows * xCols; ++i) {
        uint8_t val = xTrain[trainIndices[xTrain_i] * xRows * xCols + i];
        ret.set(i, 0, ((float) val) / (float) CHAR_MAX);
    }

    xTrain_i++;

    return ret;
}

Matrix MNistLoader::yTrainNext() {
    if (yTrain_i >= train_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    uint8_t val = yTrain[yTrain_i];
    Matrix ret(maxY + 1, 1);
    ret.set((size_t) val, 0, 1.0);

    yTrain_i++;

    return ret;
}

Matrix MNistLoader::xTestNext() {
    if (xTest_i >= test_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    Matrix ret(xRows * xCols, 1);
    for (int i = 0; i < xRows * xCols; ++i) {
        uint8_t val = xTest[xTest_i * xRows * xCols + i];
        ret.set(i, 0, ((float) (uint8_t) val) / (float) CHAR_MAX);
    }

    xTest_i++;

    return ret;
}

Matrix MNistLoader::yTestNext() {
    if (yTest_i >= test_l) {
        throw CTensorException("MNIST Loader out of bounds train");
    }

    uint8_t val = yTest[yTest_i];
    Matrix ret(maxY + 1, 1);
    ret.set((size_t) val, 0, 1.0);

    yTest_i++;

    return ret;
}

void MNistLoader::reset() {
    xTrain_i = 0;
    yTrain_i = 0;
    xTest_i = 0;
    yTest_i = 0;
    std::shuffle(trainIndices.begin(), trainIndices.end(), std::mt19937(std::random_device()()));
}
