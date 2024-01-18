//
// Created by Theo Lincke on 1/16/24.
//

#include "Network.h"
#include "Common.h"
#include "Matlib.h"
#include <sstream>

layer::layer(size_t rows, size_t cols, layer *_next, layer *_previous)
        : inputs(cols, 1, -0.5, 0.5),
          weights(rows, cols, -0.5, 0.5),
          biases(rows, 1, -0.5, 0.5),
          weightUpdates(rows, cols),
          biasUpdates(rows, 1) {
    numWeightUpdates = 0;
    numBiasUpdates = 0;
    next = _next;
    previous = _previous;
}

std::string layer::print() const {
    std::stringstream ss;
    ss << "Weights Size: " << weights.rows << ", " << weights.cols << std::endl;
    ss << "Inputs Size: " << inputs.rows << ", " << inputs.cols << std::endl;
    ss << "Biases Size: " << biases.rows << ", " << biases.cols << std::endl;
    return ss.str();
}

Network::Network(size_t numIn, size_t numOut, const std::vector<size_t> &layerSizes)
        : front(nullptr), back(nullptr) {

    if (layerSizes.empty()) {
        front = new layer(numOut, numIn, nullptr, nullptr);
        back = front;
        return;
    }

    front = new layer(layerSizes[0], numIn, nullptr, nullptr);
    layer *head = front;

    for (int i = 0; i < layerSizes.size() - 1; ++i) {
        auto *next = new layer(layerSizes[i + 1], layerSizes[i], nullptr, head);
        head->next = next;
        head = next;
    }

    head->next = new layer(numOut, layerSizes.back(), nullptr, head);
    back = head->next;
}

Network::~Network() {
    layer *head = back;
    while (head != nullptr) {
        auto *temp = head;
        head = head->next;
        delete temp;
    }
}

std::string Network::print() const {
    layer *head = front;
    std::stringstream ss;
    while (head != nullptr) {
        ss << *head << std::endl;
        head = head->next;
    }
    return ss.str();
}

Matrix Network::evaluate(const Matrix &_input) {
    if (_input.cols != front->inputs.cols || _input.rows != front->inputs.rows) {
        throw CTensorException("Network Shape error");
    }
    layer *head = front;
    head->inputs.copyFrom(_input);
    while (head->next != nullptr) {
        head->next->inputs = matMul(head->weights, head->inputs);
        matAdd_inline(head->next->inputs, head->biases);
        relu_inline(head->next->inputs);
        head = head->next;
    }

    Matrix ret = matMul(head->weights, head->inputs);
    matAdd_inline(ret, head->biases);
    softMax_inline(ret);

    return ret;
}

// TODO - do math for bias updates
void Network::update(Matrix &out, const Matrix &expected, float alpha, bool apply) {
    layer *head = back;

    // dL/dz = (e - o) https://towardsdatascience.com/derivative-of-the-softmax-function-and-the-categorical-cross-entropy-loss-ffceefc081d1
    Matrix d = matSub(out, expected);
    Matrix update(1, 1);

    while (head != nullptr) {
        // wi - dc/dwi = wi - d * input^T
        head->inputs.T_inline();
        update = matMul(d, head->inputs);
        matAdd_inline(head->weightUpdates, update);
        head->numWeightUpdates++;
        if (apply) {
            std::cout << "Updating" << std::endl;
            matScalarMult_inline(head->weightUpdates, (float) alpha / (float) head->numWeightUpdates);
            matSub_inline(head->weights, head->weightUpdates);
            head->weightUpdates.zero_inline();
            head->numWeightUpdates = 0;
        }
        head->inputs.T_inline();

        matAdd_inline(head->biasUpdates, d);
        head->numBiasUpdates++;
        if (apply) {
            matScalarMult_inline(head->biasUpdates, (float) alpha / (float) head->numBiasUpdates);
            matSub_inline(head->biases, head->biasUpdates);
            head->biasUpdates.zero_inline();
            head->numBiasUpdates = 0;
        }

        // Update d
        if (head->previous != nullptr) {
            // di = WiT * di+1 O r'
            head->weights.T_inline();
            d = matMul(head->weights, d);
            head->weights.T_inline();
            reluPrimeFromOutput_inline(head->inputs);
            matHadMul_inline(d, head->inputs);
        }

        head = head->previous;
    }
}
