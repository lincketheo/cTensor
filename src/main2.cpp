#include <matLib.hpp>
#include <Network.hpp>
#include <iostream>

using namespace matlib;
using namespace NetworkLib;
using std::stoi;

int main(int argc, char ** argv){
    /*
    int a, b, c, d;    

    if(argc == 5){
        a = stoi(argv[1]);
        b = stoi(argv[2]);
        c = stoi(argv[3]);
        d = stoi(argv[4]);
    }else{
        a = 5;
        b = 5;
        c = 2;
        d = 10;
    }

    Network myNet(a, b, c, d);
    myNet.printNetworkSummary();
    myNet.printNetwork();

    Matrix inputMat(a, 1, 2);
    printf("INPUT\n");
    inputMat.print();

    Matrix t1 = myNet.propogateNetwork(inputMat);

    printf("OUTPUT\n");
    t1.print();
    */

    Matrix A(2, 2, 10);

    Matrix M = !A;
    A.print();
    M.print();
    (A * M).print();

 //   A.print();
 //   A.GaussJordanRREF();
 //   A.print();

    return 0;

}

