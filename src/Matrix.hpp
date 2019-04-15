#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>

namespace matlib{
    namespace kernel{   //maybe overkill, but in the future it'd
                        // be cool to have differnt types of matrix datastructures
                        //ex sparse matrix, matrix, diagonal etc.
	    class Matrix{
		    public:
			    Matrix(int, int);
			    Matrix(std::string);
                Matrix(int, int, int);
		    	~Matrix();
			
    			void augment(Matrix);
                int dim1;
                int dim2;
            

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
                vector<float> elements;
                vector<int> rows;
                vector<int> cols;
                float normEuclid();
                Matrix transpose(); //just switch rows and cols
                Matrix inverse();
	    };
    }
    kernel::Matrix mat_add(kernel::Matrix, Matrix);
    kernel::Matrix mat_mul(kernel::Matrix, Matrix);
    kernel::Matrix inverse(kernel::Matrix);
	kernel::Matrix transpose(kernel::Matrix);
    kernel::Matrix rref(kernel::Matrix); //rref will just rref it, should be augmented already
    kernel::Matrix solveSystem(kernel::Matrix, kernel::Matrix); 
}



#endif
