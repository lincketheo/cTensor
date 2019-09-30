#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <vector>

// Matlib used for matrix calculations and operations
namespace matlib {
// A matrix is a vector of floats

template <typename T>
class Matrix
{
public:

  Matrix();                  

  Matrix(const std::string&); 

  Matrix(const size_t, const size_t);           

  Matrix(const size_t,
         const size_t,
         const T); 

  virtual ~Matrix() = default;

  int dim1; // rows
  int dim2; // cols



private:
  void print(); // handy print function

  void insert(int, int, const T&); 
  float get(const size_t, const size_t);

  // common matrix functions
  T normEuclid(); // euclidian / frobenius norm
  T getMax();     // maximum value (not index)
  int getMaxIndex();  // maximum index

public:
  //================================Operators==================================
  // unary opperators
  Matrix operator-();
  Matrix operator=(const float*);

  // binary operrators
  Matrix operator+(Matrix const&);
  Matrix operator-(Matrix const&);
  Matrix operator*(Matrix const&);
  Matrix operator*(float const&);
  Matrix operator+=(Matrix const&);
  Matrix operator-=(Matrix const&);
  Matrix operator*=(Matrix const&);

  // Relational operators
  bool operator<(Matrix const&);
  bool operator>(Matrix const&);
  bool operator==(Matrix const&);
  bool operator<=(Matrix const&);
  bool operator>=(Matrix const&);

  // type casting
  operator float();

  Matrix operator!(); // inverse (!tensor)
  Matrix operator*(); // transpose (*tensor)
  float operator~();  // trace (~tensor)

private:
  std::vector<std::vector<T>> arr; // A matrix
};


namespace linfunc {
void parAdd(const Matrix&, Matrix&); // Assembly like , add const to mutable
T innerProd(const Matrix&, const Matrix&);
Matrix augment(const Matrix&, const Matrix&);
Matrix getRow(const Matrix&, size_t);
Matrix getCol(const Matrix&, size_t);
bool swapRow(Matrix&, size_t, size_t);
bool swapCol(Matrix&, size_t, size_t);
bool replaceRow(Matrix&, const Matrix&, size_t);
bool toGaussJordan(Matrix&);
bool toGaussJordanRREF(Matrix&);
Matrix GaussJordan(Matrix&);
Matrix GaussJordanRREF(Matrix&);
Matrix copy_std_mult(const Matrix&, const Matrix&);
bool scalar_mult(const Matrix&, Matrix&);
bool is_singular(const Matrix&);
Matrix transpose(const Matrix&);
Matrix inverse(const Matrix&);
T trace(const Matrix&);
}
}
#endif
