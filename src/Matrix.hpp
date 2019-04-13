#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>

template <class T>
namespace matlib{
	struct element{
        int row;
        int col;
        T val;
	};
    
	class Matrix{
		public:
			Matrix(int, int);
			Matrix(std::string);
            Matrix(int, int, int);
			~Matrix();
			
			void augment(Matrix);
            int rows;
            int cols;
            

            //TODO - fix operators to work with matrices
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
		    operator float(); //typecasts  to normEuclid()

		    Matrix operator !(); //inverse (!tensor)
		    Matrix operator *(); //transpose (*tensor)
		    float operator ~(); //trace (~tensor)         
			
		private:
            //never used - only used in the opperator
            vector<element> elements;
            float normEuclid();
            Matrix mat_add(Matrix);
		    Matrix mat_mul(Matrix);
            Matrix scalarMult(float);
            Matrix transpose();
            Matrix inverse();
	};
    Matrix mat_add(Matrix, Matrix);
    Matrix mat_mul(Matrix, Matrix);
    Matrix inverse(Matrix);
	Matrix transpose(Matrix);
    Matrix rref(Matrix); //rref will just rref it, should be augmented already
    Matrix solveSystem(Matrix, Matrix);
   
}



#endif
