#include <vector>
#pragma once



class Tensor
{
	public:
		//Tensor is an ordered matrix
		Tensor();
		Tensor(int dim1, int dim2);
		Tensor(int dim1, int dim2, int desiredMax);
		~Tensor();

		//the tensor in its purest
		float * arr;


		//print the tensor in a neat format
		void print();

		//insert a value at the index (deletes val at that index)
		void insert(int c1, int c2, float val);

		float get(int c1, int c2);

		//Matrix algebra
		Tensor add(Tensor tensor);
		//stdMult is the standard algorithm, might impliment faster algorithms later
		Tensor stdMult(Tensor tensor);

		Tensor transpose();

		//return a two by two array of dim1, dim2
		int * getShape();

		//changes all values x to 1 / (1 + e^-x)
		Tensor sigmoid();

		/* Future Functions include:
		 * 	inverse
		 */
		float normEuclid();
		float getMax();
		Tensor inverse();
		

	private:
		int dim1;
		int dim2;

		void doubleCapacity();
};
