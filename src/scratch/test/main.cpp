#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace matlib;

int main(){

    Matrix<float> * mainPtr;

    SparseMatrix<float> mainSps(5, 5);

    mainPtr = &mainSps;

    mainPtr->print();


    
    return 0;


}
