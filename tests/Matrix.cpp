//
// Created by Theo Lincke on 1/11/24.
//

#include <gtest/gtest.h>
#include <cmath>
#include "Matrix.h"
#include "Matlib.h"
#include "Network.h"

TEST(MatrixTest, BasicConstructor) {
    Matrix a = Matrix(10, 5);
    EXPECT_EQ(a.rows, 10);
    EXPECT_EQ(a.cols, 5);

    // Initializes to 0
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 5; ++col) {
            EXPECT_EQ(a.get(row, col), 0.0);
        }
    }

    // Set all values to random values
    std::vector<float> randVec(10 * 5);
    for (float &i: randVec) {
        i = (float) rand() / (float) RAND_MAX;
    }

    // Set then get all values and make sure they're equal to the vector values
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 5; ++col) {
            a.set(row, col, randVec[10 * row + col]);
            EXPECT_EQ(a.get(row, col), randVec[10 * row + col]);
        }
    }

    // Set all values to random values
    for (float &i: randVec) {
        i = (float) rand() / (float) RAND_MAX;
    }
}

TEST(MatrixTest, Print) {
    Matrix a = Matrix(3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            a.set(i, j, i * 4 + j);
        }
    }

    std::stringstream ss;
    ss << a;
    const char *expected =
            "Matrix([[0,1,2,3]\n"
            "[4,5,6,7]\n"
            "[8,9,10,11]], rows = 3, cols = 4)\n";
    EXPECT_EQ(ss.str(), expected);
}

TEST(MatrixTest, Copy) {
    Matrix a = Matrix(3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            a.set(i, j, (float) rand() / (float) RAND_MAX);
        }
    }

    Matrix b(4, 5);
    EXPECT_EQ(b.cols, 5);
    EXPECT_EQ(b.rows, 4);
    b.copyFrom(a);
    EXPECT_EQ(b.cols, 4);
    EXPECT_EQ(b.rows, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(b.get(i, j), a.get(i, j));
        }
    }
}

TEST(MatrixTest, MatMul) {
    Matrix a = Matrix(2, 3);
    Matrix b = Matrix(3, 4);

    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, row * a.cols + col + 1);
        }
    }
    for (int row = 0; row < b.rows; ++row) {
        for (int col = 0; col < b.cols; ++col) {
            b.set(row, col, row * b.cols + col + 1);
        }
    }

    Matrix c = matMul(a, b);
    EXPECT_EQ(c.cols, 4);
    EXPECT_EQ(c.rows, 2);

    EXPECT_EQ(c.get(0, 0), 38);
    EXPECT_EQ(c.get(0, 1), 44);
    EXPECT_EQ(c.get(0, 2), 50);
    EXPECT_EQ(c.get(0, 3), 56);
    EXPECT_EQ(c.get(1, 0), 83);
    EXPECT_EQ(c.get(1, 1), 98);
    EXPECT_EQ(c.get(1, 2), 113);
    EXPECT_EQ(c.get(1, 3), 128);
}

TEST(MatrixTest, MatAdd) {
    Matrix a = Matrix(2, 3);
    Matrix b = Matrix(2, 3);

    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, row * a.cols + col + 1);
            b.set(row, col, row * a.cols + col + 1);
        }
    }

    Matrix c = matAdd(a, b);
    EXPECT_EQ(c.cols, 3);
    EXPECT_EQ(c.rows, 2);

    EXPECT_EQ(c.get(0, 0), 2);
    EXPECT_EQ(c.get(0, 1), 4);
    EXPECT_EQ(c.get(0, 2), 6);
    EXPECT_EQ(c.get(1, 0), 8);
    EXPECT_EQ(c.get(1, 1), 10);
    EXPECT_EQ(c.get(1, 2), 12);
}

TEST(MatrixTest, Relu) {
    Matrix a = Matrix(3, 3);

    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, (float) (row * a.cols + col) - 5);
        }
    }

    Matrix c = relu(a);
    EXPECT_EQ(c.cols, 3);
    EXPECT_EQ(c.rows, 3);

    EXPECT_EQ(c.get(0, 0), 0);
    EXPECT_EQ(c.get(0, 1), 0);
    EXPECT_EQ(c.get(0, 2), 0);
    EXPECT_EQ(c.get(1, 0), 0);
    EXPECT_EQ(c.get(1, 1), 0);
    EXPECT_EQ(c.get(1, 2), 0);
    EXPECT_EQ(c.get(2, 0), 1);
    EXPECT_EQ(c.get(2, 1), 2);
    EXPECT_EQ(c.get(2, 2), 3);
}

TEST(MatrixTest, MatSub) {
    Matrix a = Matrix(2, 3);
    Matrix b = Matrix(2, 3);

    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, row * a.cols + col + 1);
            b.set(row, col, 6);
        }
    }

    Matrix c = matSub(a, b);
    EXPECT_EQ(c.cols, 3);
    EXPECT_EQ(c.rows, 2);

    EXPECT_EQ(c.get(0, 0), -5);
    EXPECT_EQ(c.get(0, 1), -4);
    EXPECT_EQ(c.get(0, 2), -3);
    EXPECT_EQ(c.get(1, 0), -2);
    EXPECT_EQ(c.get(1, 1), -1);
    EXPECT_EQ(c.get(1, 2), 0);
}

TEST(MatrixTest, ScalarMult) {
    Matrix a = Matrix(3, 3);

    for (int row = 0; row < a.rows; ++row) {
        for (int col = 0; col < a.cols; ++col) {
            a.set(row, col, (float) (row * a.cols + col) - 5);
        }
    }

    Matrix c = matScalarMult(a, 3);
    EXPECT_EQ(c.cols, 3);
    EXPECT_EQ(c.rows, 3);

    EXPECT_EQ(c.get(0, 0), -15);
    EXPECT_EQ(c.get(0, 1), -12);
    EXPECT_EQ(c.get(0, 2), -9);
    EXPECT_EQ(c.get(1, 0), -6);
    EXPECT_EQ(c.get(1, 1), -3);
    EXPECT_EQ(c.get(1, 2), 0);
    EXPECT_EQ(c.get(2, 0), 3);
    EXPECT_EQ(c.get(2, 1), 6);
    EXPECT_EQ(c.get(2, 2), 9);
}


TEST(MatrixTest, Transpose) {
    Matrix a = Matrix(3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            a.set(i, j, i * 4 + j);
        }
    }

    a.T_inline();
    EXPECT_EQ(a.rows, 4);
    EXPECT_EQ(a.cols, 3);

    EXPECT_EQ(a.get(0, 0), 0);
    EXPECT_EQ(a.get(0, 1), 4);
    EXPECT_EQ(a.get(0, 2), 8);
    EXPECT_EQ(a.get(1, 0), 1);
    EXPECT_EQ(a.get(1, 1), 5);
    EXPECT_EQ(a.get(1, 2), 9);
    EXPECT_EQ(a.get(2, 0), 2);
    EXPECT_EQ(a.get(2, 1), 6);
    EXPECT_EQ(a.get(2, 2), 10);
    EXPECT_EQ(a.get(3, 0), 3);
    EXPECT_EQ(a.get(3, 1), 7);
    EXPECT_EQ(a.get(3, 2), 11);
}

TEST(Network, LossLowers) {
    Network a(10, 6, 2, 5);
    Matrix input(10, 1, 0, 1);
    Matrix expected(6, 1, 0, 1);

    float prevErr = MAXFLOAT;
    for (int i = 0; i < 1000; ++i) {
        auto out = a.evaluate(input);
        float nextErr = squaredErrorCost(out, expected);
        EXPECT_GT(prevErr, nextErr);
        prevErr = nextErr;

        a.update(out, expected, 0.0001);
    }
}
