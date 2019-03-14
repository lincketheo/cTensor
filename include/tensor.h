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


		float normEuclid();
		float getMax();
		float costFunc(Tensor);	
		//Tensor delCdelZ(Tensor, Tensor, Tensor);
		
		//unary opperators
		Tensor operator -();
		//INVERSE --- Tensor operator !();

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
		
		//input output

	//private: goota change some stuff before i make these private again
		int * getShape();	
		Tensor add(Tensor);
		Tensor minus(Tensor);
		Tensor stdMult(Tensor);
		Tensor scalarMult(float);
		Tensor innerProd(Tensor);
		Tensor transpose();
		Tensor sigmoid();
		Tensor sigmoidPrime();

};
#endif
