#ifndef CTENSOR_MATRIX_H
#define CTENSOR_MATRIX_H

#include <iostream>
#include <vector>
#include "Common.h"

class Matrix {
public:
    Matrix() = delete;

    Matrix(size_t rows, size_t cols);

    Matrix(size_t rows, size_t cols, float min, float max);

    Matrix(const Matrix &m);

    ~Matrix();

    float get(size_t row, size_t col) const;

    void set(size_t row, size_t col, float val);

    friend std::ostream &operator<<(std::ostream &os, Matrix const &tc) {
        return os << tc.print();
    }

    Matrix &operator=(const Matrix &m) {
        if (&m != this) {
            copyFrom(m);
        }
        return *this;
    }

    void copyFrom(const Matrix &from);

    void T_inline();

    void zero_inline();

    size_t rows;   //rows
    size_t cols;   //cols

private:
    std::string print() const;

    float *data;
    bool isTranspose;
};

#endif
