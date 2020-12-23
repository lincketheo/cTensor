#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream> 	// Print functions
#include <vector>   	// Vector for matrix
#include <cmath>		// exp
#include <random> 	 	// rand
#include <stdexcept> 	// Dim missmatch
#include <sstream> 	 	// Constructing matrix from string
#include <string.h>		// strtok

//Matlib used for matrix calculations and operations
namespace matlib{
	//A matrix is a vector of floats
	class Matrix
	{
		public:
            // ========== CONSTRUCTORS ==========
		 	Matrix();				    //standard - 2 x 2 zeros matrix
  		    Matrix(std::string);		//creates a matrix from a string input
			Matrix(int, int);		    //n x m matrix with zeros  down the diagonal (identity)
			Matrix(int, int, float);	//n x m matrix with random numbers constrained by float
	
			void print();			   //handy print function
			
			//common matrix functions
			float normEuclid();		    //euclidian / frobenius norm
			float getMax();			    //maximum value (not index)
			float getMaxAbs();			//maximum value (not index)
  		    int getMaxIndex();		    //maximum index
		

			//================================Operators==================================	
            // I had a lot of fun learning about operator overloaders
         
            // TODO
            // Setter operators
            // Matrix operator [](int);
            // Matrix operator [][](int);

			//unary opperators
			Matrix operator -();
			void operator =(const Matrix&);

			//binary operrators
			Matrix operator +(Matrix const &);
			Matrix operator -(Matrix const &);
			Matrix operator *(Matrix const &);
			Matrix operator *(float const &);		
			void operator +=(Matrix const &);
			void operator -=(Matrix const &);
			void operator *=(float const &);


			//Relational operators
		
			bool operator <(Matrix const &);
			bool operator >(Matrix const &);
			bool operator ==(Matrix const &);
			bool operator <=(Matrix const &);
			bool operator >=(Matrix const &);	
			
			//type casting
			operator float(); 

            // Binary Operators
			Matrix operator !(); //inverse (!tensor)
			Matrix operator *(); //transpose (*tensor)
			float operator ~();  //trace (~tensor)

            // Row / Col operators
            /*
             * Normally I would use subscript operator overloads, but I
             * always hate using subscripts, I like functional swappers instead
             * much more explicit
             */
            void swapRow(const int&, const int&);		    //swaps two rows with each other
            void swapCol(const int&, const int&);		    //swaps two cols with each other
            void replaceRow(const int&, const Matrix&);   	//replaces a row with a desired row vector
            void replaceCol(const int&, const Matrix&);   	//replaces a column with a desired column vector
            Matrix getRow(const int&);			    		//returns a matrix that resembles the row provided
            Matrix getCol(const int&);			    		//returns a matrix that resembles the collumn provided

			void GaussJordan();
			void GaussJordanRREF();
			float trace();


			void insert(const int&, const int&, const float&);	//insert an element
			float get(const int&, const int&) const;			
			void set(const Matrix&);
            Matrix scalarMult(const float&);	    //multiply matrix by a scalar
			int dim1;   //rows
			int dim2;   //cols
			std::vector<float> arr;	 //A matrix

		protected:
            // Return a new matrix
			Matrix add(const Matrix&);             // Adds another matrix of equal dimension
			Matrix minus(const Matrix&);           // Subtracts anotehr matrix of equal dimension
			Matrix stdMult(const Matrix&);		   // standard multiplication (ie no fancy algorithm)
			Matrix transpose();             // Return a new Transpose of this matrix
			Matrix inverse();               // Returns the inverse of this matrix
            

            // Operates on self
			void self_add(const Matrix&);             	// Adds another matrix of equal dimension
			void self_minus(const Matrix&);           	// Subtracts anotehr matrix of equal dimension
	};


	// BASICMATH
	float random_float(const float&, const float&);

	// MATRIX MATH
	Matrix rotate(Matrix, float, int, int); //rotate a matrix
	Matrix parMult(Matrix, Matrix); //parallel multiplication
	Matrix parAdd(Matrix, Matrix); //parallel addition
	Matrix parSqr(Matrix); //parallel sqaring
	
}
#endif
