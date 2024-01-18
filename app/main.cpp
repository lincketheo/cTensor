//
// Created by tjl on 1/17/24.
//

#include <iostream>
#include "MNistLoader.h"
#include "Network.h"
#include "Matlib.h"

float trainLoop(Network &net, MNistLoader &loader, bool verbose, float alpha) {
    // Test loop
    float err = 0.0;
    if (verbose) {
        std::cout << "Train Loop Loss:" << std::endl;
    }
    size_t batchSize = 256;
    Matrix x(1, 1);
    Matrix y(1, 1);
    Matrix out(1, 1);
    for (int i = 0; i < loader.train_l; ++i) {
        x = loader.xTrainNext();
        y = loader.yTrainNext();
        out = net.evaluate(x);

        net.update(out, y, alpha, i == loader.train_l - 1);

        float _err = categoricalCrossEntropy(y, out);
        if (verbose && (i + 1) % 1000 == 0) {
            std::cout << "\r" << (i + 1) << "/" << loader.train_l << ": " << _err << std::flush;
        }
        err += _err;
    }

    std::cout << out << y << std::endl;
    loader.reset();
    std::cout << std::endl;
    return err;
}

float testLoop(Network &net, MNistLoader &loader, bool verbose) {
    // Test loop
    if (verbose) {
        std::cout << "Test Loop Accuracy:" << std::endl;
    }

    int correct = 0;
    int total = 0;

    for (int i = 0; i < loader.test_l; ++i) {
        Matrix x = loader.xTestNext();
        Matrix y = loader.yTestNext();
        auto out = net.evaluate(x);

        int rowE, colE;
        int rowA, colA;
        argMax(out, &rowA, &colA);
        argMax(y, &rowE, &colE);

        if (rowA == rowE) {
            correct++;
        }
        total++;

        if (verbose && (i + 1) % 1000 == 0) {
            std::cout << "\r" << (i + 1) << "/" << loader.test_l << ": " << correct << "/" << total << " = "
                      << (float) correct / (float) total
                      << std::flush;
        }
    }
    loader.reset();
    std::cout << std::endl;
    return (float) correct / (float) total;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>.npz" << std::endl;
        return 1;
    }

    MNistLoader loader(argv[1]);
    std::cout << loader.maxY << std::endl;
    Network net(loader.xCols * loader.xRows, loader.maxY + 1, {30});
    std::cout << net << std::endl;

    Matrix x = loader.xTrainNext();
    Matrix y = loader.yTrainNext();

    try {
        testLoop(net, loader, true);

        for (int epoch = 0; epoch < 100; ++epoch) {
            std::cout << "Epoch: " << epoch << std::endl;

            // Train loop
            trainLoop(net, loader, true, 0.1);

            // Test loop
            testLoop(net, loader, true);
        }
    } catch (CTensorException &e) {
        std::cerr << e.what << std::endl;
    }
}
