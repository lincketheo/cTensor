

#include "Matrix.hpp"
#include <iostream>

using namespace matlib;

int main(int argc, char ** argv){

    Matrix a(3, 3, 10);
    Matrix b(3, 3, 10);

    a.print();
    b.print();

    Matrix d = a + b;
    d.print();
    a += b;
    a.print();
    a *= 10;
    a.print();
    a -= b;
    a.print();

    d = a * b;
    d.print();



    return 1;
}

