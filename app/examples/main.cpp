//
// Created by tjl on 1/17/24.
//

#include <iostream>
#include "MNistLoader.h"
#include "Network.h"
#include "Matlib.h"

float testLoop(Network &net, MNistLoader &loader, bool verbose) {
    // Test loop
    float err = 0.0;
    if (verbose) {
        std::cout << "Test Loop Loss:" << std::endl;
    }
    for (int i = 0; i < loader.test_l; ++i) {
        Matrix x = loader.xTestNext();
        Matrix y = loader.yTestNext();
        auto out = net.evaluate(x);
        float _err = squaredErrorCost(out, y);
        if (verbose && (i + 1) % 20 == 0) {
            std::cout << "\r" << (i + 1) << "/" << loader.test_l << ": " << _err << std::flush;
        }
        err += _err;
    }
    loader.reset();
    std::cout << std::endl;
    return err;
}

float trainLoop(Network &net, MNistLoader &loader, bool verbose, float alpha) {
    // Test loop
    float err = 0.0;
    if (verbose) {
        std::cout << "Train Loop Loss:" << std::endl;
    }
    for (int i = 0; i < loader.train_l; ++i) {
        Matrix x = loader.xTrainNext();
        Matrix y = loader.yTrainNext();
        auto out = net.evaluate(x);
        float _err = squaredErrorCost(out, y);
        net.update(out, y, alpha);
        if (verbose && (i + 1) % 20 == 0) {
            std::cout << "\r" << (i + 1) << "/" << loader.train_l << ": " << _err << std::flush;
        }
        err += _err;
        if (i == loader.train_l - 1) {
            std::cout << out << std::endl;
            std::cout << y << std::endl;
            exit(1);
        }
    }
    loader.reset();
    std::cout << std::endl;
    return err;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>.npz" << std::endl;
        return 1;
    }

    int epochs = 10;

    MNistLoader loader(argv[1]);
    Network net(loader.xCols * loader.xRows, loader.maxY + 1, 2, 100);

    try {
        testLoop(net, loader, true);

        for (int epoch = 0; epoch < epochs; ++epoch) {
            std::cout << "Epoch: " << epoch << std::endl;
            // Train loop
            trainLoop(net, loader, true, 0.0001);

            // Test loop
            testLoop(net, loader, true);
        }
    } catch (CTensorException &e) {
        std::cerr << e.what << std::endl;
    }
}
