/**
    CS-11 Asn 2, kernel.cpp
    Purpose: Basic low level matrix  kernel opperations

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/

#include <iostream>
#include "Matrix.hpp"


using namespace matlib::kernel;

/**
    Encodes a sparse identiy matrix of dimension 1 and 2

    @param d1, d2 two dimensions of the matrix, rows x cols respectively
    @return void a sparse matrix of initialized dim1 dim2 d1 d2 and rows and
    cols containing identity values
*/
Matrix::Matrix(int d1, int d2) {
    dim1 = d1;
    dim2 = d2;
    for(register int i = 0; i < d1 && i < d2; i++) {
        rows.push_back(i);
        cols.push_back(i);
        elements.push_back(1);
    }
}

/**
    Returns a matrix from input using classic matrix notation
    i.e. [a, b, c; e, f, g; h, i, j].

    @param input matrix in string format
    @return a matrix of dimension specified in the string
*/
Matrix::Matrix(std::string str) {
    std::stringstream ss;
    ss << str;
    std::string row;
    while(getline(ss, row, ';')) {
        std::stringstream ssrow;
        ssrow << row;
        std::string element;
        int curr;
        matlib::element* prev;

        while(getline(ssrow, element, ' ')) {

        }
    }
}


//Matrix destructor - dereferences pointers and vectors
Matrix::~Matrix();

/**
    Augments self with included matrix as long as dim match

    @param input Matrix of same dim1 as self
    @return alters Matrix cols and rows
*/
Matrix::augment(Matrix);

//returns the most simple frobineous / euclidian norm to a matrix / vector respectively
float Matrix::normEuclid();

//returns the transpose of self - only a col row swap
Matrix Matrix::transpose();

//returns inverse of self
Matrix Matrix::inverse();

//Operators - utilize the above kernel functions

//Unitary operators
//returns negative self
Matrix operator -();

//creates a new matrix  encoded by float array
Matrix operator =(const float *);

//binary operrators
//Add a matrix to self
Matrix operator +(Matrix const &);
//subtract a matrix from self
Matrix operator -(Matrix const &);
//Multiply a matrix by self
Matrix operator *(Matrix const &);
//multiply a float by self
Matrix operator *(float const &);
//Add and a matrix and set equal to self
Matrix operator +=(Matrix const &);
//Substract a matrix and set equal to self
Matrix operator -=(Matrix const &);
//Multiply a matrix and set equal to self
Matrix operator *=(Matrix const &);

//Relational operators
bool operator <(Matrix const &);
bool operator >(Matrix const &);
bool operator ==(Matrix const &);
bool operator <=(Matrix const &);
bool operator >=(Matrix const &);

//type casting
operator float(); //typecasts  to normEuclid()

Matrix operator !(); //inverse (!tensor)
Matrix operator *(); //transpose (*tensor)
float operator ~(); //trace (~tensor)
