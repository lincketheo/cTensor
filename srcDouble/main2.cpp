#include <matLib.hpp>
#include <Network.hpp>
#include <iostream>

using namespace matlib;
using namespace NetworkLib;
using std::stoi;

int main(int argc, char ** argv){
    srand((unsigned int)time(NULL));

    Matrix t1 = Matrix(5, 1, 4);
    Matrix t2 = Matrix(5, 1, 4);
    t1.print();
    t2.print();
    t1.sigmoid().print();
    parMult(t1, t2).print();
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
    
    Matrix expected(b, 1);

    myNet.backPropogateRecurs(t1, expected, 2);
    myNet.printNetwork();

    Matrix t2 = myNet.propogateNetwork(inputMat);
    
    printf("EXPECTED\n");
    expected.print();
    printf("INPUT\n");
    inputMat.print();
    printf("OUTPUT1\n");
    t1.print();
    printf("OUTPUT2\n");
    t2.print();

    Matrix t3 = t2 - t1;
    t3.print();
*/
/*
    Matrix A(20, 20, 10);

    Matrix M = !A;
    A.print();
    M.print();
    (A * M).print();

 //   A.print();
 //   A.GaussJordanRREF();
 //   A.print();
*/
    return 0;
}

