#include "Matrix.h"       //main header
#include "Common.h"
#include <sstream>

Matrix::Matrix(size_t _rows, size_t _cols) {
    if (_rows < 1 || _cols < 1) {
        throw CTensorException("Rows and cols must be greater than 1");
    }
    rows = _rows;
    cols = _cols;
    isTranspose = false;
    data = new float[rows * cols];
}

Matrix::Matrix(size_t _rows, size_t _cols, float min, float max) {
    if (_rows < 1 || _cols < 1) {
        throw CTensorException("Rows and cols must be greater than 1");
    }
    rows = _rows;
    cols = _cols;
    isTranspose = false;
    data = new float[rows * cols];

    if (max < min) {
        throw CTensorException("Max is less than Min");
    }
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float random = ((float) rand()) / (float) RAND_MAX;
            set(row, col, min + (max - min) * random);
        }
    }
}

float Matrix::get(size_t row, size_t col) const {
    if (row >= rows || col >= cols) {
        throw CTensorException("Row or Col is too large");
    }
    if (!isTranspose) {
        return data[row + rows * col];
    } else {
        return data[col + cols * row];
    }
}

void Matrix::set(size_t row, size_t col, float val) {
    if (row >= rows || col >= cols) {
        throw CTensorException("Row or Col is too large");
    }
    if (!isTranspose) {
        data[row + rows * col] = val;
    } else {
        data[col + cols * row] = val;
    }
}

std::string Matrix::print() const {
    std::stringstream ret;

    ret << "Matrix([";
    for (int i = 0; i < rows; ++i) {
        ret << "[";
        for (int j = 0; j < cols; ++j) {
            if (j == cols - 1) {
                if (i == rows - 1) {
                    ret << get(i, j) << "]], rows = " << rows << ", cols = " << cols << ")\n";
                } else {
                    ret << get(i, j) << "]\n";
                }
            } else {
                ret << get(i, j) << ",";
            }
        }
    }
    return ret.str();
}

void Matrix::copyFrom(const Matrix &from) {
    if (from.rows * from.cols != rows * cols) {
        delete data;
        cols = from.cols;
        rows = from.rows;
        data = new float[rows * cols];
    }
    memcpy(data, from.data, sizeof(float) * cols * rows);
}

void Matrix::T_inline() {
    isTranspose = !isTranspose;
    size_t temp = cols;
    cols = rows;
    rows = temp;
}
