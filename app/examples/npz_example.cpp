//
// Created by tjl on 1/17/24.
//

#include <iostream>
#include "NPZReader.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>.npz" << std::endl;
        return 1;
    }

    cnpy::npz_t npz = cnpy::npz_load(argv[1]);

    for (auto & it : npz) {
        std::cout << it.first << std::endl;
    }

    return 0;
}