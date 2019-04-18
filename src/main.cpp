#include <matLib.hpp>
#include <Network.hpp>
#include <iostream>

using namespace matlib;
using namespace NetworkLib;

int main(){
    Network myNet(5, 5, 4, 10);
    myNet.printNetworkSummary();
    myNet.printNetwork();

    Matrix inputMat(5, 1, 2);
    printf("INPUT\n");
    inputMat.print();

    Matrix t1 = myNet.propogateNetwork(inputMat);

    printf("OUTPUT\n");
    t1.print();

    return 0;
}

