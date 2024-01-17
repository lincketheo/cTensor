//
// Created by Theo Lincke on 1/16/24.
//

#include "Network.h"
#include "Common.h"
#include "Matlib.h"
#include <sstream>

layer::layer(size_t rows, size_t cols, layer *_next, layer *_previous)
        : inputs(cols, 1, 0, 1),
          weights(rows, cols, 0, 1),
          biases(rows, 1, 0, 1) {
    next = _next;
    previous = _previous;
}

std::string layer::print() const {
    std::stringstream ss;
    ss << "Input Size: " << weights.cols << ", Output Size: " << weights.rows << std::endl;
    ss << "Inputs: " << inputs << std::endl;
    ss << "Biases: " << biases << std::endl;
    ss << "Weights: " << weights << std::endl;
    return ss.str();
}

Network::Network(size_t numIn, size_t numOut, size_t layers, size_t layersSize)
        : input(nullptr), output(nullptr) {
    if (layers < 1) {
        throw CTensorException("Must have more than 1 layer");
    }

    if (layers == 1) {
        input = new layer(numOut, numIn, nullptr, nullptr);
        output = input;
        return;
    }

    input = new layer(layersSize, numIn, nullptr, nullptr);
    layer *head = input;
    for (int i = 0; i < layers - 2; ++i) {
        auto *next = new layer(layersSize, layersSize, nullptr, head);
        head->next = next;
        head = next;
    }
    head->next = new layer(numOut, layersSize, nullptr, head);
    output = head->next;
}

Network::~Network() {
    layer *head = input;
    while (head != nullptr) {
        auto *temp = head;
        head = head->next;
        delete temp;
    }
}

std::string Network::print() const {
    layer *head = input;
    std::stringstream ss;
    while (head != nullptr) {
        ss << *head << std::endl;
        head = head->next;
    }
    return ss.str();
}

Matrix evaluateRecursive(const layer *l) {
    if (l->next == nullptr) {
        Matrix out = matMul(l->weights, l->inputs);
        relu_inline(out);
        return out;
    }
    l->next->inputs = matMul(l->weights, l->inputs);
    matAdd_inline(l->next->inputs, l->biases);
    relu_inline(l->next->inputs);
    return evaluateRecursive(l->next);
}

Matrix Network::evaluate(const Matrix &_input) {
    if (_input.cols != input->inputs.cols || _input.rows != input->inputs.rows) {
        throw CTensorException("Network Shape error");
    }
    input->inputs.copyFrom(_input);
    return evaluateRecursive(input);
}

// TODO - do math for bias updates
void Network::update(Matrix &out, const Matrix &expected, float alpha) {
    layer *head = output;

    // dL = 2 * (e - o) O r'
    Matrix d = matSub(out, expected);
    matScalarMult_inline(d, 2);
    reluPrimeFromOutput_inline(out);
    matHadMul_inline(d, out);

    while (head != nullptr) {
        // wi - dc/dwi = wi - d * input^T
        head->inputs.T_inline();
        Matrix update = matMul(d, head->inputs);
        matScalarMult_inline(update, alpha);
        matSub_inline(head->weights, update);
        head->inputs.T_inline();

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
