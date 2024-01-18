//
// Created by tjl on 1/17/24.
//

#include <iostream>
#include "MNistLoader.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>.npz" << std::endl;
        return 1;
    }

    MNistLoader loader(argv[1]);

    for (int i = 0; i < 2; ++i) {
        std::cout << loader.xTestNext() << std::endl;
        std::cout << loader.yTestNext() << std::endl;
    }

    return 0;
}
