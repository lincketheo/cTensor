//
// Created by Theo Lincke on 1/16/24.
//
#include <iostream>
#include "Matrix.h"
#include "Common.h"

int main() {
    try {
        std::cout << "Making new matrix: " << std::endl;
        auto matrix = Matrix(2, 5, 0, 10);
        std::cout << "Making new matrix:" << std::endl;
        Matrix m2 = matrix;
        m2 = Matrix(5, 4);
        std::cout<<m2<<std::endl;
        std::cout << "Done" << std::endl;
        return 0;
    } catch (const CTensorException &e) {
        std::cout << e.what << std::endl;
        return 1;
    }
}
