//
// Created by Theo Lincke on 1/16/24.
//

#ifndef CTENSOR_NETWORK_H
#define CTENSOR_NETWORK_H

#include "Matrix.h"

struct layer {
    layer(size_t rows, size_t cols, layer *_next, layer *_previous);

    Matrix inputs;

    Matrix biases;
    Matrix biasUpdates;
    size_t numBiasUpdates;

    Matrix weights;
    Matrix weightUpdates;
    size_t numWeightUpdates;

    layer *next;
    layer *previous;

    friend std::ostream &operator<<(std::ostream &os, layer const &tc) {
        return os << tc.print();
    }

private:
    std::string print() const;
};

class Network {
public:
    Network(size_t numIn, size_t numOut, const std::vector<size_t> &layerSizes);

    Network() = delete;

    ~Network();

    friend std::ostream &operator<<(std::ostream &os, Network const &tc) {
        return os << tc.print();
    }

    Matrix evaluate(const Matrix &input);

    void update(Matrix &out, const Matrix &expected, float alpha, bool apply);

private:
    layer *front;
    layer *back;

    std::string print() const;
};


#endif //CTENSOR_NETWORK_H
