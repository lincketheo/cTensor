#ifndef TENSOR_H
#define TENSOR_H




class Tensor
{
	public:
		//Tensor is an ordered matrix
		Tensor();
		Tensor(int, int);
		Tensor(int, int, int);
		//~Tensor();

		int dim1;
		int dim2;

		float * arr;

		void print();

		void insert(int, int, float);
		float get(int, int);
		
		//common matrix functions
		float normEuclid();
		float getMax();
		float costFunc(Tensor); //uneccessary	
		

		//================================Operators==================================	
		//unary opperators
		Tensor operator -();
		Tensor operator =(const float *);

		//binary operrators
		Tensor operator +(Tensor const &);
		Tensor operator -(Tensor const &);
		Tensor operator *(Tensor const &);
		Tensor operator *(float const &);		
		Tensor operator +=(Tensor const &);
		Tensor operator -=(Tensor const &);
		Tensor operator *=(Tensor const &);


		//Relational operators
		
		bool operator <(Tensor const &);
		bool operator >(Tensor const &);
		bool operator ==(Tensor const &);
		bool operator <=(Tensor const &);
		bool operator >=(Tensor const &);	
			
		//type casting
		operator float(); 

		Tensor operator !(); //inverse (!tensor)
		Tensor operator *(); //transpose (*tensor)
		float operator ~(); //trace (~tensor)


		//indexing

		//global operations
		Tensor sigmoid();
		Tensor sigmoidPrime();
		Tensor innerProd(Tensor);
	    Tensor augment(Tensor);
        Tensor getRow(int);
        Tensor getCol(int);
        void replaceRow(int, Tensor);
        void replaceCol(int, Tensor);
        void swapRow(int, int);
        void swapCol(int, int);
        void rref();	

	private:
		Tensor add(Tensor);
		Tensor minus(Tensor);
		Tensor stdMult(Tensor);
		Tensor scalarMult(float);
		Tensor transpose();
		Tensor inverse();
		float trace();
    
		

};

//Tensor library

Tensor parAdd(Tensor, Tensor);
Tensor parMult(Tensor, Tensor);
Tensor parSqr(Tensor);
Tensor weightGrad(Tensor, Tensor, Tensor, Tensor);


//TODO
float pNorm();
Tensor mat_maul(Tensor, Tensor);
Tensor rotate(Tensor, float, int, int);
Tensor rref(Tensor);
Tensor normalize(Tensor);
Tensor solveFor(Tensor, Tensor); //Ax = b
bool linInd(Tensor);
Tensor grahmSchmitt(Tensor, Tensor);
float * fourier(Tensor);
bool orthogonal(Tensor, Tensor);


#endif
