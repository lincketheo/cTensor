/**
    CS-11 Asn 2, operators.cpp
    Purpose: Overridden operators for matrix calculations

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/
#include <matLib.hpp>

using namespace matlib;

//===================================== MATRIX OPERATIONS =======================================

//Make matrix negative
Matrix Matrix::operator -(){
        Matrix result = Matrix(dim1, dim2);
        for(int i = 0; i < dim1 * dim2; i++)
                result.arr[i] = -arr[i];
        return result;
}

//add a matrix to self
Matrix Matrix::operator +(const Matrix &tensor){
        return this->add(tensor);
}

//subtract a matrix from self
Matrix Matrix::operator -(const Matrix &tensor){
        return this->minus(tensor);
}

//multiply a matrix to self
Matrix Matrix::operator *(const Matrix &tensor){
        return this->stdMult(tensor);
}

//multiply a scalar by self
Matrix Matrix::operator *(const float &val){
        return this->scalarMult(val);
}

//====================================== COMPARATOR OPERATIONS ======================================

bool Matrix::operator <(const Matrix &tensor){
    Matrix newTens = tensor;
        return (this->normEuclid()) < (newTens.normEuclid());
}
bool Matrix::operator >(const Matrix &tensor){
    Matrix newTens = tensor;
        return (this->normEuclid()) > (newTens.normEuclid());
}
bool Matrix::operator ==(const Matrix &tensor){
    Matrix newTens = tensor;
        return (this->normEuclid()) == (newTens.normEuclid());
}
bool Matrix::operator <=(const Matrix &tensor){
        Matrix newTens = tensor;
        return (this->normEuclid()) <= (newTens.normEuclid());
}
bool Matrix::operator >=(const Matrix &tensor){
        Matrix newTens = tensor;
        return (this->normEuclid()) >= (newTens.normEuclid());
}


//====================================== UNITARY OPERATIONS ======================================
//norm of self
Matrix::operator float(){
    return this->normEuclid();
}

//inverse (!A)
Matrix Matrix::operator !(){
    return this->inverse();
}

//transpose self (*A)
Matrix Matrix::operator *(){
    return this->transpose();
}

//trace of self (~A)
float Matrix::operator ~(){
    return this->trace();
}
