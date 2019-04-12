#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>

namespace matlib{
	struct element{
		element *left = NULL;
		element *right = NULL;
		element *up = NULL;
		element *down = NULL;

		bool visited;

		int val;
	};
    
	class Matrix{
		public:
			Matrix();
			Matrix(std::string str);
			~Matrix();
			
			void augment(Matrix m);
            

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
            //never used - only used in the opperators
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


template <typename T>
//only fill if != 0
vector<T> rowIndices;
vector<T> colIndices;
vector<T> val;



#endif
