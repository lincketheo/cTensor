/**
    CS-11 Asn 2, kernel.cpp
    Purpose: Basic low level matrix  kernel opperations

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/
#include <iostream>
#include "Matrix.hpp"

#define DIM_MISMATCH "err dim mismatch line"
#define COMPARE(a, b) (a > b)
#define INCREMENT(a, b) ((a > b) ? b++ : a++)


using namespace matlib;

/**
    Encodes a sparse identiy matrix of dimension 1 and 2

    @param d1, d2 two dimensions of the matrix, rows x cols respectively
    @return void a sparse matrix of initialized this->dim1 this->dim2 d1 d2 and rows and
    cols containing identity values
*/
template <class T>
SparseMatrix<T>::SparseMatrix(int d1, int d2) {
    this->dim1 = d1;
    this->dim2 = d2;
    for(int i = 0; i <= d1 && i <= d2; i++) {
        rows.push_back(i + 1);
        cols.push_back(i + 1);
        elements.push_back(1);
    }
}

/**
    Returns a matrix from input using classic matrix notation
    i.e. [a, b, c; e, f, g; h, i, j].

    @param input matrix in string format
    @return a matrix of dimension specified in the string
*/
/*
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
*/

//Matrix destructor - dereferences pointers and vectors
template <class T>
SparseMatrix<T>::~SparseMatrix(){
    
}

template <class T>
void SparseMatrix<T>::print(){
    int x = 1;
    int y = 1;
    int i = 0;
    while(y <= this->dim1){
        if(rows[i] == x && cols[i] == y){
            printf("%.1f ", elements[i]);
            //printf("\n%d %d\n ", rows[i], cols[i]);
            i++;
        }else{
            printf("0.0 ");
        }
        if(x == this->dim2){
            x = 1;
            y ++;
            printf("\n");
        }else{
            x++;
        }
    }
    printf("\n");
}

/**
    adds Matrix input to self and updates self

    @param Matrix to add to self
    @returns updated version of self
    throws dim mismatch if invalid dimensions
*/
template <class T>
void SparseMatrix<T>::add(SparseMatrix<T> m){
    int i = 0; //indexes self
    int j = 0; //indexes m

    if(this->dim1 != m.dim1 || this->dim2 != m.dim2){
        printf("Err dim mismatch\n");
        return;
    }

    while(i < m.dim1 && j < this->dim1){

        if(m.cols[i] > cols[j]){
            j++;
        }
        else if(m.cols[i] < cols[j]){
            i++;
        }
        else{
            if(m.rows[i] == rows[j] && m.cols[i] == cols[j]){
                elements[j]+=m.elements[i];
                i++;
                j++;
            }
            else if(m.rows[i] > rows[j])j++;
            else if(m.rows[i] < rows[j])i++;
        }
    }
}

template <class T>
void SparseMatrix<T>::stdMult(SparseMatrix<T> m){
    

}
/*
void insertVal(int row, int col, float val){
    for(int i = 0; i < rows.size(); i++){
        if(rows[i] > row && cols[i] == col || rows[i] == row && cols[i]
    }
}
*/
//returns the most simple frobineous / euclidian norm to a matrix / vector respectively
//float Matrix::normEuclid();

//returns the transpose of self - only a col row swap
//Matrix Matrix::transpose();

//returns inverse of self
//Matrix Matrix::inverse();
/*
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
*/

int main(){
    Matrix<float> matptr ;
    SparseMatrix<float> a(5, 5);
    matptr = a;
    matptr.print();
    return 0;


}

