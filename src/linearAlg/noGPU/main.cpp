#include "tensor.h"
#include <iostream>

int main(){
    Tensor myTens(4, 3);
    myTens.print();
    myTens.swapRow(0, 2);

    myTens.print();
    return 0;
}

