//
// Created by Theo Lincke on 1/16/24.
//

#include "Matlib.h"
#include "Common.h"
#include <cmath>
#include <limits>

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
            ret += std::pow(std::abs(a.get(row, col)), p);
        }
    }
    return ret;
}

float squaredErrorCost(const Matrix &a, const Matrix &b) {
    Matrix diff = matSub(a, b);
    return pNorm(diff, 2);
}

float categoricalCrossEntropy(const Matrix &expected, const Matrix &actual) {
    float ret;
    for (int row = 0; row < expected.rows; ++row) {
        for (int col = 0; col < expected.cols; ++col) {
            float _expected = expected.get(row, col);
            if (_expected != 0.0) {
                ret += _expected * std::log(actual.get(row, col));
            }
        }
    }
    return -ret;
}

void softMax_inline(Matrix &a) {
    float denominator = 0.0;
    Matrix cache(a.rows, a.cols);

    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            cache.set(row, col, std::exp(a.get(row, col)));
            denominator += cache.get(row, col);
        }
    }
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, cache.get(row, col) / denominator);
        }
    }
}

Matrix softMax(const Matrix &a) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    softMax_inline(ret);
    return ret;
}

void argMax(const Matrix &a, int *_row, int *_col) {
    float ret = std::numeric_limits<float>::min();
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            if (a.get(row, col) > ret) {
                ret = a.get(row, col);
                *_row = row;
                *_col = col;
            }
        }
    }
}

void normalize_inline(Matrix &a) {
    float norm = pNorm(a, 2);
    matScalarMult_inline(a, 1 / norm);
}

Matrix normalize(const Matrix &a) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    normalize_inline(ret);
    return ret;
}

bool hasNan(const Matrix &a) {
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            if (std::isnan(a.get(row, col))) {
                return true;
            }
        }
    }
    return false;
}

bool hasInf(const Matrix &a) {
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            if (std::isinf(a.get(row, col))) {
                return true;
            }
        }
    }
    return false;
}

Matrix sigmoid(const Matrix &a) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    sigmoid_inline(ret);
    return ret;
}

void sigmoid_inline(Matrix &a) {
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, 1 / (1 + std::exp(-a.get(row, col))));
        }
    }
}

Matrix sigmoidPrimeFromOutput(const Matrix &a) {
    Matrix ret(a.rows, a.cols);
    ret.copyFrom(a);
    sigmoidPrimeFromOutput_inline(ret);
    return ret;
}

void sigmoidPrimeFromOutput_inline(Matrix &a) {
    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, (a.get(row, col) * (1 - a.get(row, col))));
        }
    }
}
