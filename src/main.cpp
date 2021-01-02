

#include "Matrix.hpp"
#include "CNN.hpp"
#include <iostream>

using namespace matlib;
using namespace NetworkLib;

int main(int argc, char ** argv){


    CNN c({4, 3});
    c.print_network_summary();
    c.print_network();
    
    std::unique_ptr<Matrix> a = std::make_unique<Matrix>("1; 2; 3; 4");
    a->print();
    c.print_inputs();
    c.propogate_network(std::move(a));
    c.print_inputs();


    return 1;
}

