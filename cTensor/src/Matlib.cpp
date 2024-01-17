//
// Created by Theo Lincke on 1/16/24.
//

#include "Matlib.h"
#include "Common.h"

Matrix matMul(const Matrix &a, const Matrix &b) {
    if (a.cols != b.rows) {
        throw CTensorException("matrix multiply dimension error");
    }
    Matrix ret(a.rows, b.cols);
    for (int aRow = 0; aRow < a.rows; ++aRow) {
        for (int bCol = 0; bCol < b.cols; ++bCol) {
            float val = 0.0;
            for (int aCol = 0; aCol < a.cols; ++aCol) {
                val += a.get(aRow, aCol) * b.get(aCol, bCol);
            }
            ret.set(aRow, bCol, val);
        }
    }
    return ret;
}

Matrix matAdd(const Matrix &a, const Matrix &b) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    matAdd_inline(ret, b);
    return ret;
}

void matAdd_inline(Matrix &a, const Matrix &b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw CTensorException("matrix add dimension exception");
    }
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, a.get(row, col) + b.get(row, col));
        }
    }
}

void relu_inline(Matrix &a) {
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            if (a.get(row, col) < 0) {
                a.set(row, col, 0);
            }
        }
    }
}

Matrix relu(const Matrix &a) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    relu_inline(ret);
    return ret;
}

void reluPrimeFromOutput_inline(Matrix &a) {
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            if (a.get(row, col) > 0) {
                a.set(row, col, 1);
            }
        }
    }
}

Matrix reluPrimeFromOutput(const Matrix &a) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    reluPrimeFromOutput_inline(ret);
    return ret;
}


Matrix matSub(const Matrix &a, const Matrix &b) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    matSub_inline(ret, b);
    return ret;
}

void matSub_inline(Matrix &a, const Matrix &b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw CTensorException("matrix subtraction dimension exception");
    }
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, a.get(row, col) - b.get(row, col));
        }
    }
}

Matrix matScalarMult(const Matrix &a, float b) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    matScalarMult_inline(ret, b);
    return ret;
}

void matScalarMult_inline(Matrix &a, float b) {
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, b * a.get(row, col));
        }
    }
}


Matrix matHadMul(const Matrix &a, const Matrix &b) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    matHadMul_inline(ret, b);
    return ret;
}

void matHadMul_inline(Matrix &a, const Matrix &b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw CTensorException("Hadamard product dimension mismatch");
    }
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, b.get(row, col) * a.get(row, col));
        }
    }
}

float pNorm(const Matrix &a, float p) {
    float ret = 0.0;
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            ret += pow(abs(a.get(row, col)), p);
        }
    }
    return ret;
}

float squaredErrorCost(const Matrix &a, const Matrix &b) {
    Matrix diff = matSub(a, b);
    return pNorm(diff, 2);
}

