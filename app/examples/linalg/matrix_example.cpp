//
// Created by Theo Lincke on 1/16/24.
//
#include <iostream>
#include <Matrix.h>
#include "Common.h"

int main() {
    try {
        auto matrix = Matrix(2, 5);
        for(int i = 0; i < 2; ++i){
            for(int j = 0; j < 5; ++j){
                matrix.set(i, j, i*5 + j);
            }
        }
        std::cout << matrix << std::endl;
        std::cout << matrix.get(0, 1);
        return 0;
    } catch (const CTensorException &e) {
        std::cout << e.what << std::endl;
        return 1;
    }
}
