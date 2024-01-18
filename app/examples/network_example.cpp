//
// Created by Theo Lincke on 1/16/24.
//

#include "Network.h"
#include "Matlib.h"

int main() {
    Network a(10, 6, {5, 4});
    Matrix input(10, 1, 0, 1);
    Matrix expected(6, 1, 0, 1);
    try {
        Matrix out = a.evaluate(input);
        std::cout << squaredErrorCost(out, expected) << std::endl;
        for (int i = 0; i < 1000; ++i) {
            a.update(out, expected, 0.0001, true);
            out = a.evaluate(input);
            std::cout << squaredErrorCost(out, expected) << std::endl;
        }
    } catch (const CTensorException &e) {
        std::cout << e.what << std::endl;
    }

    return 0;
}