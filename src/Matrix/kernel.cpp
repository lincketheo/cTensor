/**
    CS-11 Asn 2, kernel.cpp
    Purpose: Basic low level matrix  kernel opperations

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/
#include <iostream>         //printf std
#include "matLib.hpp"       //main header
#include <cmath>            //exp
#include <random>           //rand
#include <stdexcept>        //dim missmatch
#include <sstream>          //Constructor Matrix
#include <vector>           //vector

#define MIN(a, b) ((a > b) ? b : a)

using namespace matlib;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::stringstream;
using std::invalid_argument;


/**
    Utility random function

    @param a min value b max value
    @return a random float  between a and b
*/
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

//================== Constructors ==================

/**
    Builds matrix from string input

    @param str string matrix input
    @return self matrix build using standard matlab notation
    (i.e. [a b c; d e f; g h i])

*/

Matrix::Matrix(string str) {
	vector<float> varr;
	stringstream ss;
    ss << str;
	string row;
	dim1 = 0;
	dim2 = 0;
	bool firstPass = true;
    while(getline(ss, row, ';')) {
		dim1++;
		stringstream ssrow;
        ssrow << row;
        string element;
        while(getline(ssrow, element, ' ')) {
			dim2 = (firstPass) ? dim2+1 : dim2;
			varr.push_back(stof(element));
        }
		firstPass = false;
    }
    arr = vector<float>(dim1 * dim2);
	for(int i = 0; i < dim1*dim2; i++)
		arr[i] = varr[i];
}


//    Default constructor Creates a a two by two matrix with zeros in all indexes
Matrix::Matrix(){
    dim1 = 2;
    dim2 = 2;
    arr = vector<float>(dim1 * dim2); 
    for(int i = 0; i < dim1 * dim2; i++)
        arr[i] = 0;
}

/**
    Encodes an identiy matrix of dimension d1 and d2 - neglects lower rows if extra (0 rows)

    @param d1, d2 two dimensions of the matrix, rows x cols respectively
    @return void a sparse matrix of initialized this->dim1 this->dim2 d1 d2 and rows and
    cols containing identity values
*/
Matrix::Matrix(int d1, int d2){
    dim1 = d1;
    dim2 = d2;
    arr = vector<float>(dim1 * dim2);
    for(int i = 0; i < dim1 * dim2; i++)
		arr[i] = (i % (dim2 + 1) == 0 && i < dim2 * dim2) ? 1 : 0;
}

/**
    Encodes an matrix of dimension d1 and d2 with random values all below desiredMax
    Used in initializing neural network - randomized matrices

    @param d1, d2 two dimensions of the matrix, rows x cols respectively and the max random
    value to the matrix

    @return void a sparse matrix of initialized this->dim1 this->dim2 d1 d2 and rows and
    cols containing identity values
*/
Matrix::Matrix(int d1, int d2, float desiredMax){
    dim1 = d1;
    dim2 = d2;
    arr = vector<float>(dim1 * dim2);
    for(int i = 0; i < dim1 * dim2; i++)
        arr[i] = RandomFloat(-desiredMax, desiredMax);
}


//================== USEFUL FUNCTIONS ==================
/**
    prints matrix in an easy to read manner (rows x cols)

    3 decimal places
*/
void Matrix::print(){
    printf("\n");
    for(int i = 0; i < dim1; i ++){
        for(int j = 0; j < dim2; j++)
            printf("%f ", arr[(i*dim2)+j]);
        printf("\n");
    }
    printf("\n");
}


/**
    inserts a value into the matrix    

    @param c1, c2 indices for the row, col respectively (starting at 0)
    val value to insert

    @return updated version of self where matrix index c1, c2 has  val
*/
void Matrix::insert(int c1, int c2, float val){
    if(c1 >= dim1 || c2 >= dim2)return;
    arr[(dim2 * c1) + c2] = val;
}

/**
    inserts a value into the matrix    

    @param c1, c2 indices for the row, col respectively (starting at 0)

    @return value at matrix index c1, c2
*/
float Matrix::get(int c1, int c2){
    return arr[(dim2 * c1) + c2];
}

/**
    gets a vertical vector from the matrix

    @param col, the collumn to extract from the matrix
    @return all values on the collumn specified as a new vertical matrix
*/
Matrix Matrix::getCol(int col){
    Matrix newTens(dim1, 1);
    for(int i = 0; i < dim1; i++)
        newTens.insert(i, 0, get(i, col));
    return newTens;
}

/**
    gets a horizontal vector from the matrix

    @param row, the row to extract from the matrix
    @return all values on the row specified as a new horizontal matrix
*/
Matrix Matrix::getRow(int row){
    Matrix newTens(1, dim2);
    for(int i = 0; i < dim2; i++)
        newTens.insert(0, i, get(row, i));
    return newTens;
}

//TODO allow this opperation to replace more than just one row
/**
    replaces a row in the matrix with a horizontal matrix of the same dim2

    @param row, the row to replace with horizontal matrix t
*/
void Matrix::replaceRow(int row, Matrix t){
    for(int i = 0; i < dim2; i++){
        insert(row, i, t.get(0, i));
    }
}

/**
    replaces a col in the matrix with a vertical matrix of the same dim1

    @param col, the col to replace with vertical matrix t
*/
void Matrix::replaceCol(int col, Matrix t){
    for(int i = 0; i < dim1; i++)
        insert(i, col, t.get(i, 0));
}

/**
    swaps to rows in the matrix

    @param r1, r2, the two rows of the matrix to swap
*/
void Matrix::swapRow(int r1, int r2){
    Matrix temp = getRow(r1);
    replaceRow(r1, getRow(r2));
    replaceRow(r2, temp);
}

/**
    swaps two cols in the matrix

    @param c1, c2, the two collumns of the matrix to swap
*/
void Matrix::swapCol(int c1, int c2){
    Matrix temp = getCol(c1);
    replaceCol(c1, getCol(c2));
    replaceCol(c2, temp);
}

//================== MATRIX OPERATIONS LOGIC ==================
//Adds matrix tensor to self
Matrix Matrix::add(Matrix tensor){
    Matrix newMatrix = Matrix(dim1, dim2);
    if(dim1 != tensor.dim1 || dim2 != tensor.dim2)
        throw invalid_argument("dim missmatch add");             
    for(int i = 0; i < dim1 * dim2; i++)
        newMatrix.arr[i] = arr[i] + tensor.arr[i];
    return newMatrix;
}

//subtracts matrix tensor from self
Matrix Matrix::minus(Matrix tensor){
        Matrix newMatrix = Matrix(dim1, dim2);
        if(dim1 != tensor.dim1 || dim2 != tensor.dim2)
                throw invalid_argument("dim missmatch minus");             
        for(int i = 0; i < dim1 * dim2; i++)
                newMatrix.arr[i] = arr[i] - tensor.arr[i];
        return newMatrix;
}

//multiplies self by a scalar
Matrix Matrix::scalarMult(float val){
        Matrix newMatrix = Matrix(dim1, dim2);
        for(int i = 0; i < dim1 * dim2; i++)
                newMatrix.arr[i] = arr[i] * val;
        return newMatrix;
}

//inner product of two matrices
Matrix Matrix::innerProd(Matrix tensor){
        Matrix newMatrix = Matrix(dim1, dim2);
        if(dim1 != tensor.dim1 || dim2 != tensor.dim2)
            throw invalid_argument("dim missmatch innerProduct");                
        for(int i = 0; i < dim1 * dim2; i++)
                newMatrix.arr[i] = arr[i] * tensor.arr[i];
        return newMatrix;
}

//standard matrix multiplication (not optimized)
Matrix Matrix::stdMult(Matrix tensor){
    Matrix newMatrix = Matrix(dim1, tensor.dim2);
    if(dim2 != tensor.dim1)
        throw invalid_argument("dim missmatch stdMult");
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < tensor.dim2; j++){
            float temp = 0;
            for(int x = 0; x < dim2; x++)
                temp += tensor.get(x, j) * get(i, x);
            newMatrix.insert(i, j, temp);
        }
    }
    return newMatrix;
}

//returns self  with the sigmoid function applied
Matrix Matrix::sigmoid(){
    Matrix newTens = Matrix(dim1, dim2);
    for(int i = 0; i < dim1 * dim2; i++)
        newTens.arr[i] = 1.0 / (1.0 + exp(-arr[i]));
    return newTens;
}

//returns self with the sigmoid prime function applied
Matrix Matrix::sigmoidPrime(){
        Matrix newTens = Matrix(dim1, dim2);
        for(int i = 0; i < dim1 * dim2; i++){
                newTens.arr[i] = (1.0 / (1.0 + exp(1.0 * -arr[i]))) * (1 - (1.0 / (1.0 + exp(1.0 * -arr[i]))));
        }
        return newTens;
}

//Relu function on self
Matrix Matrix::relu(){
    Matrix newTens = Matrix(dim1, dim2);
        for(int i = 0; i < dim1 * dim2; i++){
            if(arr[i] < 0)newTens.arr[i] = 0;
            else newTens.arr[i] = arr[i];
        }
        return newTens;
}

//prime relu function on self
Matrix Matrix::reluPrime(){
    Matrix newTens = Matrix(dim1, dim2);
        for(int i = 0; i < dim1 * dim2; i++){
            if(arr[i] < 0)newTens.arr[i] = 0;
            else newTens.arr[i] = 1;
        }
        return newTens;
}


//returns transposed version of self
Matrix Matrix::transpose(){
    Matrix transpose = Matrix(dim2, dim1);
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++)
            transpose.insert(j, i, get(i, j));
    }
    return transpose;
}

//returns the euclidian / frobenius norm of self
float Matrix::normEuclid(){
    float n = 0;
    for(int i = 0; i < dim1 * dim2; i++)
        n+=arr[i]*arr[i];
    return sqrt(n);
}

//returns the maximum value in the matrix
float Matrix::getMax(){
    if(dim1 * dim2 == 0)
        return 0;
    float max = arr[0];
    for(int i = 0; i < dim1*dim2; i++)
        max = arr[i] > max ? arr[i] : max;
    return max;
}

//returns the maximum index of a matrix
int Matrix::getMaxIndex(){
    if(dim2 != 1)return 0;
    int max = 0;
    for(int i = 0; i < dim1; i++){
        if(arr[i] > arr[max])max = i;
    }
    return max;
}

//Returns inverse of self
Matrix Matrix::inverse(){
    Matrix inverse(dim1, dim2);
    Matrix large(dim1, dim2 * 2);
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++)
            large.insert(i, j, get(i, j));
        for(int j = dim2; j < dim2 * 2; j++)
            large.insert(i, j, inverse.get(i, j - dim2));
    }
    large.GaussJordanRREF();
    for(int i = 0; i < dim2; i++){
        for(int j = 0; j < dim1; j++)
            inverse.insert(i, j, large.get(i, j + dim1));
    }
    return inverse;
}

//returns the trace of self
float Matrix::trace(){
    float n = 0;
    for(int i = 0; i < dim1 && i < dim2; i++)
        n += get(i, i);
    return n;
}

/**
    rotates a vector by keeping the norm the same and appling a rotational matrix onto self

    @param t1, the matrix to rotate, theta how  many degrees, x, y, the two dimensions to rotate
    @return a new matrix  that is rotated by  theta degrees
*/
Matrix rotate(Matrix t1, float theta, int x, int y)
{
        Matrix newTens(t1.dim1, t1.dim1);
        newTens.insert(x, x, cos(theta));
        newTens.insert(y, x, sin(theta));
        newTens.insert(y, y, cos(theta));
        newTens.insert(x, y, -sin(theta));
        return newTens * t1;
}

//multiplies all values in parallel
Matrix matlib::parMult(Matrix t, Matrix t2){
    Matrix t1(t.dim1, t.dim2);
    if(t1.dim1 != t2.dim1 || t1.dim2 != t2.dim2)
        throw invalid_argument("dim missmatch parMult");
    for(int i = 0; i < t1.dim1 * t1.dim2; i++)
        t1.arr[i] = t.arr[i] * t2.arr[i];
    return t1;
}

//adds all values in parallel
Matrix matlib::parAdd(Matrix t, Matrix t2){
    Matrix t1 = t;
    if(t1.dim1 != t2.dim1)
        throw invalid_argument("dim missmatch parAdd");
    for(int i = 0; i < t2.dim1; i ++){
        for(int j = 0; j < t1.dim2; j++)
            t1.insert(i, j, t1.get(i, j) + t2.get(i, 1));
    }
    return t1;
}

//squares all values in parallel (self par mult self)
Matrix matlib::parSqr(Matrix t){
    Matrix t1 = t;
    for(int i = 0; i < t1.dim1 * t1.dim2; i++)
          t1.arr[i] = t1.arr[i] * t1.arr[i];
    return t1;
}

//Returns principal eigenvector  using the recursive technique
Matrix Matrix::principalEig(int max_iter){
    Matrix v = Matrix(dim1, 1);
    v = (v * (1 / float(v)));
    for(int i = 0; i < max_iter; i++){
        v = stdMult(v);
        v = (v * (1 / float(v)));
    }
    return v;
}

//executes gaussjordan algorithm on self (1's down diagonal and upper traingular)
void Matrix::GaussJordan(){
    int i = 0;
    int j = 0;
    while(i < dim1 && j < dim2){
        int s = 1;
        while(get(i, j) == 0 && i + s < dim1 - 1){
            swapRow(i, s);
        }
        if(get(i, j) != 0){
            Matrix _temp = getRow(i);
            Matrix temp = _temp * (1 / get(i, j));
            replaceRow(i, temp);
            for(int x = 1; i + x < dim1; x++){
                if(get(i+x, j) != 0){
                    Matrix temp2 = getRow(x + i) - (temp * (get(i + x, j)));
                    replaceRow(i + x, temp2);
                }
            }
        }
        j++;
        i++;
    } 
}

//Executes the GaussJordan RREF (reduced row echelon form) on self
void Matrix::GaussJordanRREF(){
    GaussJordan();
    int startingRow = MIN(dim1, dim2);
    int i = startingRow - 1;
    int j = i; 
    while(i >= 0){
        if(get(i, j) != 0){
            Matrix temp = getRow(i);
            for(int x = 1; i - x >= 0; x ++){
                Matrix temp2 = getRow(i - x) - (temp * (get(i - x, j)));
                replaceRow(i - x, temp2);
            }
        }  
        i--;
        j--;
    }
}
