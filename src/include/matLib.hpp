#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

namespace matlib{

    class Matrix
    {
	    public:
	    	//Matrix is an ordered matrix
	     	Matrix();
            Matrix(std::string);
    		Matrix(int, int);
    		Matrix(int, int, int);
    		//~Matrix();
    
    		int dim1;
    		int dim2;
    
    		float * arr;
    
    		void print();
    
    		void insert(int, int, float);
    		float get(int, int);
    		
    		//common matrix functions
    		float normEuclid();
    		float getMax();
    		float costFunc(Matrix); //uneccessary	
		

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
		    Matrix sigmoid();
		    Matrix sigmoidPrime();
		    Matrix innerProd(Matrix);
	        Matrix augment(Matrix);
            Matrix getRow(int);
            Matrix getCol(int);
            void swapRow(int, int);
            void swapCol(int, int);
            void rref();	
            void replaceRow(int, Matrix);
            void replaceCol(int, Matrix);
            Matrix principalEig(int);
            void GaussJordan();
            void GaussJordanRREF();

	    private:
		    Matrix add(Matrix);
		    Matrix minus(Matrix);
		    Matrix stdMult(Matrix);
		    Matrix scalarMult(float);
		    Matrix transpose();
		    Matrix inverse();
	    	float trace();
    
		

    };
    Matrix rotate(Matrix, float, int, int);
    Matrix parMult(Matrix, Matrix);
    Matrix parAdd(Matrix, Matrix);
    Matrix parSqr(Matrix);
    
}

#endif
