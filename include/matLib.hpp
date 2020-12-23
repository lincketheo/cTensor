#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <vector>

//Matlib used for matrix calculations and operations
namespace matlib{
	//A matrix is a vector of floats
	class Matrix
	{
		public:
			//Matrix is an ordered matrix
		 	Matrix();				   //standard - 2 x 2 zeros matrix
  		Matrix(std::string);		//creates a matrix from a string input
			Matrix(int, int);		   //n x m matrix with zeros  down the diagonal (identity)
			Matrix(int, int, float);	//n x m matrix with random numbers constrained by float
	
			int dim1;   //rows
			int dim2;   //cols
	
			std::vector<float> arr;	 //A matrix
	
			void print();			   //handy print function
	
			void insert(int, int, float);	   //insert an element
			float get(int, int);			
			
			//common matrix functions
			float normEuclid();		 //euclidian / frobenius norm
			float getMax();			 //maximum value (not index)
  		int getMaxIndex();		  //maximum index
		

			//================================Operators==================================	
			//unary opperators
			Matrix operator -();
			Matrix operator =(const float *);

			//binary operrators
			Matrix operator +(Matrix const &);
			Matrix operator -(Matrix const &);
			Matrix operator *(Matrix const &);
			Matrix operator *(float const &);		
			Matrix operator +=(Matrix const &);
			Matrix operator -=(Matrix const &);
			Matrix operator *=(Matrix const &);


			//Relational operators
		
			bool operator <(Matrix const &);
			bool operator >(Matrix const &);
			bool operator ==(Matrix const &);
			bool operator <=(Matrix const &);
			bool operator >=(Matrix const &);	
			
			//type casting
			operator float(); 

			Matrix operator !(); //inverse (!tensor)
			Matrix operator *(); //transpose (*tensor)
			float operator ~(); //trace (~tensor)


			//global operations
  		Matrix sigmoid();			   //sigmoid function sig = 1 / (1 + e^(-x))
	  	Matrix sigmoidPrime();		  //sigmoid prime function (sig)(1 - sig)
	  	Matrix relu();				  //relu function (0 if negative value if positive)
	  	Matrix reluPrime();			 //relu prime (0 if negative 1 if positive)
	  	Matrix innerProd(Matrix);	   //inner product
	  	Matrix augment(Matrix);		 //augments two matrices
	  	Matrix getRow(int);			 //returns a matrix that resembles the row provided
	  	Matrix getCol(int);			 //returns a matrix that resembles the collumn provided
	  	void swapRow(int, int);		 //swaps two rows with each other
	  	void swapCol(int, int);		 //swaps two cols with each other
	  	void replaceRow(int, Matrix);   //replaces a row with a desired row vector
		  void replaceCol(int, Matrix);   //replaces a column with a desired column vector
		  Matrix principalEig(int);	   //returns the principal eigenvector
	  	void GaussJordan();			 //only REF (row echelon form)
	  	void GaussJordanRREF();		 //RREF (reduced row echelon form)

	  	Matrix scalarMult(float);	   //multiply matrix by a scalar
		private:
			Matrix add(Matrix);
			Matrix minus(Matrix);
			Matrix stdMult(Matrix);		 //standard multiplication
			Matrix transpose();
			Matrix inverse();
			float trace();
	
		

	};
	Matrix rotate(Matrix, float, int, int); //rotate a matrix
	Matrix parMult(Matrix, Matrix); //parallel multiplication
	Matrix parAdd(Matrix, Matrix); //parallel addition
	Matrix parSqr(Matrix); //parallel sqaring
	
}
#endif
