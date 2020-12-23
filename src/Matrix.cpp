/**
    CS-11 Asn 2, kernel.cpp
    Purpose: Basic low level matrix  opperations

    @author Theo Lincke
    @version 1.1 4/17/19
*/
#include <iostream>  //printf std
#include <cmath>     //exp
#include <random>    //rand
#include <stdexcept> //dim missmatch
#include <sstream>   //Constructor Matrix
#include <vector>    //vector

#include "Matrix.hpp" //main header

#define MIN(a, b) ((a > b) ? b : a)

using std::cin;
using std::cout;
using std::invalid_argument;
using std::string;
using std::stringstream;
using std::vector;

namespace matlib
{

    float random_float(const float &a, const float &b)
    {
        return (((float)rand()) / (float)RAND_MAX) * (b - a) + a;
    }

    //================== Constructors ==================

    Matrix::Matrix(string str)
    {
        vector<float> varr;

        // Validate first
        int rows = 0;
        int cols = 0;
        bool first = true;

        char *row;
        char *row_s;

        row = strtok_r(&str[0], ";", &row_s);
        while (row)
        {
            char *elem, *s;
            elem = strtok_r(row, " ,", &s);

            int i = 0;
            while (elem != NULL)
            {
                i++;
                varr.push_back(stof(std::string(elem)));
                elem = strtok_r(NULL, " ,", &s);
            }
            if (first)
            {
                first = false;
                cols = i;
            }
            else
            {
                if (cols != i)
                {
                    throw invalid_argument("Invalid Input String");
                }
            }
            rows++;
            row = strtok_r(NULL, ";", &row_s);
        }

        dim1 = rows;
        dim2 = cols;

        arr = vector<float>(dim1 * dim2);
        for (int i = 0; i < dim1 * dim2; i++)
            arr[i] = varr[i];
    }

    Matrix::Matrix()
    {
        dim1 = 2;
        dim2 = 2;
        arr = vector<float>(dim1 * dim2);
        for (int i = 0; i < dim1 * dim2; i++)
            arr[i] = 0;
    }

    Matrix::Matrix(int d1, int d2)
    {
        dim1 = d1;
        dim2 = d2;
        arr = vector<float>(dim1 * dim2);
        for (int i = 0; i < dim1 * dim2; i++)
            arr[i] = (i % (dim2 + 1) == 0 && i < dim2 * dim2) ? 1 : 0;
    }

    Matrix::Matrix(int d1, int d2, float desiredMax)
    {
        dim1 = d1;
        dim2 = d2;
        arr = vector<float>(dim1 * dim2);
        for (int i = 0; i < dim1 * dim2; i++)
            arr[i] = random_float(-desiredMax, desiredMax);
    }

    // Returns number of decimals preceding the decimal
    int num_decs(float a)
    {
        a = abs(a);
        int i = 0;
        while (a >= 1)
        {
            a = a / 10;
            i++;
        }
        return i;
    }

    //================== USEFUL FUNCTIONS ==================
    void Matrix::print()
    {
        printf("\n");
        int magnitude = num_decs(getMaxAbs());
        printf("%d\n", magnitude);
        for (int i = 0; i < dim1; i++)
        {
            for (int j = 0; j < dim2; j++)
            {

                float a = arr[(i * dim2) + j];

                // Number of white spaces to preceed
                int space = abs(a) < 1 ? magnitude - 1 : magnitude - num_decs(a);
                for (int x = 0; x < space; ++x)
                {
                    printf(" ");
                }

                if (a >= 0)
                    printf(" %.3f ", a);
                else
                    printf("%.3f ", a);
            }
            printf("\n");
        }
        printf("\n");
    }

    void Matrix::insert(const int &c1, const int &c2, const float &val)
    {
        if (c1 >= dim1 || c2 >= dim2){
           throw invalid_argument("Dimension bounds exceeded");
        }

        arr[(dim2 * c1) + c2] = val;
    }

    float Matrix::get(const int& c1, const int& c2) const
    {
        return arr[(dim2 * c1) + c2];
    }

    /**
    gets a vertical vector from the matrix

    @param col, the collumn to extract from the matrix
    @return all values on the collumn specified as a new vertical matrix
*/
    Matrix Matrix::getCol(const  int &col)
    {
        Matrix newTens(dim1, 1);
        for (int i = 0; i < dim1; i++)
            newTens.insert(i, 0, get(i, col));
        return newTens;
    }

    /**
    gets a horizontal vector from the matrix

    @param row, the row to extract from the matrix
    @return all values on the row specified as a new horizontal matrix
*/
    Matrix Matrix::getRow(const int &row)
    {
        Matrix newTens(1, dim2);
        for (int i = 0; i < dim2; i++)
            newTens.insert(0, i, get(row, i));
        return newTens;
    }

    //TODO allow this opperation to replace more than just one row
    /**
    replaces a row in the matrix with a horizontal matrix of the same dim2

    @param row, the row to replace with horizontal matrix t
*/
    void Matrix::replaceRow(const int &row, const Matrix &t)
    {
        for (int i = 0; i < dim2; i++)
        {
            insert(row, i, t.get(0, i));
        }
    }

    /**
    replaces a col in the matrix with a vertical matrix of the same dim1

    @param col, the col to replace with vertical matrix t
*/
    void Matrix::replaceCol(const int &col, const Matrix &t)
    {
        for (int i = 0; i < dim1; i++)
            insert(i, col, t.get(i, 0));
    }

    /**
    swaps to rows in the matrix

    @param r1, r2, the two rows of the matrix to swap
*/
    void Matrix::swapRow(const int &r1, const int &r2)
    {
        Matrix temp = getRow(r1);
        replaceRow(r1, getRow(r2));
        replaceRow(r2, temp);
    }

    /**
    swaps two cols in the matrix

    @param c1, c2, the two collumns of the matrix to swap
*/
    void Matrix::swapCol(const int &c1, const int &c2)
    {
        Matrix temp = getCol(c1);
        replaceCol(c1, getCol(c2));
        replaceCol(c2, temp);
    }

    //================== MATRIX OPERATIONS LOGIC ==================
    //Adds matrix tensor to self
    Matrix Matrix::add(const Matrix &tensor)
    {
        Matrix newMatrix = Matrix(dim1, dim2);
        if (dim1 != tensor.dim1 || dim2 != tensor.dim2)
            throw invalid_argument("dim missmatch add");
        for (int i = 0; i < dim1 * dim2; i++)
            newMatrix.arr[i] = arr[i] + tensor.arr[i];
        return newMatrix;
    }

    //subtracts matrix tensor from self
    Matrix Matrix::minus(const Matrix &tensor)
    {
        Matrix newMatrix = Matrix(dim1, dim2);
        if (dim1 != tensor.dim1 || dim2 != tensor.dim2)
            throw invalid_argument("dim missmatch minus");
        for (int i = 0; i < dim1 * dim2; i++)
            newMatrix.arr[i] = arr[i] - tensor.arr[i];
        return newMatrix;
    }

    //multiplies self by a scalar
    Matrix Matrix::scalarMult(const float &val)
    {
        Matrix newMatrix = Matrix(dim1, dim2);
        for (int i = 0; i < dim1 * dim2; i++)
            newMatrix.arr[i] = arr[i] * val;
        return newMatrix;
    }

    //standard matrix multiplication (not optimized)
    Matrix Matrix::stdMult(const Matrix &tensor)
    {
        Matrix newMatrix = Matrix(dim1, tensor.dim2);
        if (dim2 != tensor.dim1)
            throw invalid_argument("dim missmatch stdMult");
        for (int i = 0; i < dim1; i++)
        {
            for (int j = 0; j < tensor.dim2; j++)
            {
                float temp = 0;
                for (int x = 0; x < dim2; x++)
                    temp += tensor.get(x, j) * get(i, x);
                newMatrix.insert(i, j, temp);
            }
        }
        return newMatrix;
    }

    //returns transposed version of self
    Matrix Matrix::transpose()
    {
        Matrix transpose = Matrix(dim2, dim1);
        for (int i = 0; i < dim1; i++)
        {
            for (int j = 0; j < dim2; j++)
                transpose.insert(j, i, get(i, j));
        }
        return transpose;
    }

    void Matrix::self_add(const Matrix& mat){
        if (dim1 != mat.dim1 || dim2 != mat.dim2)
            throw invalid_argument("dim missmatch add");
        for (int i = 0; i < dim1 * dim2; i++)
            arr[i] = arr[i] + mat.arr[i];
    }
    void Matrix::self_minus(const Matrix& mat){
        if (dim1 != mat.dim1 || dim2 != mat.dim2)
            throw invalid_argument("dim missmatch minus");
        for (int i = 0; i < dim1 * dim2; i++)
            arr[i] = arr[i] - mat.arr[i];
    }

    //returns the euclidian / frobenius norm of self
    float Matrix::normEuclid()
    {
        float n = 0;
        for (int i = 0; i < dim1 * dim2; i++)
            n += arr[i] * arr[i];
        return sqrt(n);
    }

    //returns the maximum value in the matrix
    float Matrix::getMax()
    {
        if (dim1 * dim2 == 0)
            return 0;
        float max = arr[0];
        for (int i = 0; i < dim1 * dim2; i++)
            max = arr[i] > max ? arr[i] : max;
        return max;
    }

    float Matrix::getMaxAbs()
    {
        if (dim1 * dim2 == 0)
            return 0;
        float max = abs(arr[0]);
        for (int i = 0; i < dim1 * dim2; i++)
            max = abs(arr[i]) > max ? abs(arr[i]) : max;
        return max;
    }

    //returns the maximum index of a matrix
    int Matrix::getMaxIndex()
    {
        if (dim2 != 1)
            return 0;
        int max = 0;
        for (int i = 0; i < dim1; i++)
        {
            if (arr[i] > arr[max])
                max = i;
        }
        return max;
    }

    //Returns inverse of self
    Matrix Matrix::inverse()
    {
        Matrix inverse(dim1, dim2);
        Matrix large(dim1, dim2 * 2);
        for (int i = 0; i < dim1; i++)
        {
            for (int j = 0; j < dim2; j++)
                large.insert(i, j, get(i, j));
            for (int j = dim2; j < dim2 * 2; j++)
                large.insert(i, j, inverse.get(i, j - dim2));
        }
        large.GaussJordanRREF();
        for (int i = 0; i < dim2; i++)
        {
            for (int j = 0; j < dim1; j++)
                inverse.insert(i, j, large.get(i, j + dim1));
        }
        return inverse;
    }

    //returns the trace of self
    float Matrix::trace()
    {
        float n = 0;
        for (int i = 0; i < dim1 && i < dim2; i++)
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

    //executes gaussjordan algorithm on self (1's down diagonal and upper traingular)
    void Matrix::GaussJordan()
    {
        int i = 0;
        int j = 0;
        while (i < dim1 && j < dim2)
        {
            int s = 1;
            while (get(i, j) == 0 && i + s < dim1 - 1)
            {
                swapRow(i, s);
            }
            if (get(i, j) != 0)
            {
                Matrix _temp = getRow(i);
                Matrix temp = _temp * (1 / get(i, j));
                replaceRow(i, temp);
                for (int x = 1; i + x < dim1; x++)
                {
                    if (get(i + x, j) != 0)
                    {
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
    void Matrix::GaussJordanRREF()
    {
        GaussJordan();
        int startingRow = MIN(dim1, dim2);
        int i = startingRow - 1;
        int j = i;
        while (i >= 0)
        {
            if (get(i, j) != 0)
            {
                Matrix temp = getRow(i);
                for (int x = 1; i - x >= 0; x++)
                {
                    Matrix temp2 = getRow(i - x) - (temp * (get(i - x, j)));
                    replaceRow(i - x, temp2);
                }
            }
            i--;
            j--;
        }
    }

    void Matrix::set(const Matrix& mat){
        if (dim1 != mat.dim1 || dim2 != mat.dim2)
            throw invalid_argument("dim missmatch add");
        for (int i = 0; i < dim1 * dim2; i++)
            arr[i] = mat.arr[i];
    }

    //===================================== MATRIX OPERATIONS =======================================

    //Make matrix negative
    Matrix Matrix::operator-()
    {
        Matrix result = Matrix(dim1, dim2);
        for (int i = 0; i < dim1 * dim2; i++)
            result.arr[i] = -arr[i];
        return result;
    }

    void Matrix::operator =(const Matrix& mat)
    {
        set(mat);
    }

    //add a matrix to self
    Matrix Matrix::operator+(const Matrix &tensor)
    {
        return this->add(tensor);
    }

    //subtract a matrix from self
    Matrix Matrix::operator-(const Matrix &tensor)
    {
        return this->minus(tensor);
    }

    //multiply a matrix to self
    Matrix Matrix::operator*(const Matrix &tensor)
    {
        return this->stdMult(tensor);
    }
    
    void Matrix::operator +=(const Matrix &tensor){
        this->self_add(tensor);
    }
    void Matrix::operator -=(const Matrix &tensor){
        this->self_minus(tensor);
    }
    void Matrix::operator *=(const float &f){
        for(int i = 0; i < dim1 * dim2; ++i){
            arr[i] = arr[i] * f;
        }
    }

    //multiply a scalar by self
    Matrix Matrix::operator*(const float &val)
    {
        return this->scalarMult(val);
    }

    //====================================== COMPARATOR OPERATIONS ======================================

    bool Matrix::operator<(const Matrix &tensor)
    {
        Matrix newTens = tensor;
        return (this->normEuclid()) < (newTens.normEuclid());
    }
    bool Matrix::operator>(const Matrix &tensor)
    {
        Matrix newTens = tensor;
        return (this->normEuclid()) > (newTens.normEuclid());
    }
    bool Matrix::operator==(const Matrix &tensor)
    {
        Matrix newTens = tensor;
        return (this->normEuclid()) == (newTens.normEuclid());
    }
    bool Matrix::operator<=(const Matrix &tensor)
    {
        Matrix newTens = tensor;
        return (this->normEuclid()) <= (newTens.normEuclid());
    }
    bool Matrix::operator>=(const Matrix &tensor)
    {
        Matrix newTens = tensor;
        return (this->normEuclid()) >= (newTens.normEuclid());
    }

    //====================================== UNITARY OPERATIONS ======================================
    //norm of self
    Matrix::operator float()
    {
        return this->normEuclid();
    }

    //inverse (!A)
    Matrix Matrix::operator!()
    {
        return this->inverse();
    }

    //transpose self (*A)
    Matrix Matrix::operator*()
    {
        return this->transpose();
    }

    //trace of self (~A)
    float Matrix::operator~()
    {
        return this->trace();
    }

} // Namespace matlib
