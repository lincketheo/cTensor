#include <math.h>
#include <random>
#include <iostream>
#include "tensor.h"

//initializes tensor to a 2 x 2 zero matrix
Tensor::Tensor(){
	dim1 = 2;
	dim2 = 2;
	arr = new float[4];
	for(int i = 0; i < 4; i++){
		arr[i] = 0;
	}
}

//initializes tensor to a _dim1 * _dim2 zero matrix
Tensor::Tensor(int _dim1, int _dim2){
	dim1 = _dim1;
	dim2 = _dim2;
	arr = new float[dim1 * dim2];
	for(int i = 0; i < dim1 * dim2; i++){
		arr[i] = 0;
	}
}

Tensor::Tensor(int _dim1, int _dim2, int desiredMax){
	dim1 = _dim1;
	dim2 = _dim2;
	std::random_device rd;
	arr = new float[dim1 * dim2];
	float ratio = ((float)desiredMax) / rd.max();
	for(int i = 0; i < dim1 * dim2; i++){
		arr[i] = ratio * rd();
	}

}
//prints tensor
void Tensor::print(){
	std::cout<<std::endl;
	for(int i = 0; i < dim1; i ++){
		for(int j = 0; j < dim2; j++){
			std::cout<<arr[(i*dim2) + j] << " ";
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

//insert value at index c1, c2
void Tensor::insert(int c1, int c2, float val){
	if(c1 >= dim1 || c2 >= dim2){
		return;
	}
	arr[(dim2 * c1) + c2] = val;
}

//add two tensors
Tensor Tensor::add(Tensor tensor){
	Tensor newTensor = Tensor(dim1, dim2);
	if(dim1 != tensor.getShape()[0] || dim2 != tensor.getShape()[1]){
		//throw error message
		return newTensor;
	}
	for(int i = 0; i < dim1 * dim2; i++){
		newTensor.arr[i] = arr[i] + tensor.arr[i];
	}
	return newTensor;
}


Tensor Tensor::minus(Tensor tensor){
        Tensor newTensor = Tensor(dim1, dim2);
        if(dim1 != tensor.getShape()[0] || dim2 != tensor.getShape()[1]){
                //throw error message
                return newTensor;
        }
        for(int i = 0; i < dim1 * dim2; i++){
                newTensor.arr[i] = arr[i] - tensor.arr[i];
        }
        return newTensor;
}


Tensor Tensor::scalarMult(float val){
        Tensor newTensor = Tensor(dim1, dim2);
        for(int i = 0; i < dim1 * dim2; i++){
                newTensor.arr[i] = arr[i] * val;
        }
        return newTensor;
}

Tensor Tensor::innerProd(Tensor tensor){
        Tensor newTensor = Tensor(dim1, dim2);
        if(dim1 != tensor.getShape()[0] || dim2 != tensor.getShape()[1]){
                //throw error message
                return newTensor;
        }
        for(int i = 0; i < dim1 * dim2; i++){
                newTensor.arr[i] = arr[i] * tensor.arr[i];
        }
        return newTensor;
}


//standard matrix multiplication
Tensor Tensor::stdMult(Tensor tensor){
	Tensor newTensor = Tensor(dim1, tensor.getShape()[1]);
	if(dim2 != tensor.getShape()[0]){
		return newTensor;
	}
	for(int i = 0; i < dim1; i++){
		for(int j = 0; j < tensor.getShape()[1]; j++){
			float temp = 0;
			for(int x = 0; x < dim2; x++){
				temp += tensor.get(x, j) * get(i, x);
			}
			newTensor.insert(i, j, temp);
		}
	}
	return newTensor;
}

//return value at index c1, c2
float Tensor::get(int c1, int c2){
	return arr[(dim2 * c1) + c2];
}

//returns a array[2] array[0] is dim1 array[1] is dim2
int * Tensor::getShape(){
	int * a = new int[2];
	a[0] = dim1;
	a[1] = dim2;
	return a;
}



Tensor Tensor::sigmoid(){
	Tensor newTens = Tensor(dim1, 1);
	for(int i = 0; i < dim1 * dim2; i++){
		//because this will always void be a dim1 x 1 array;
		newTens.insert(i, 0, 1 / (1 + exp(-arr[i])));

	}
	return newTens;
}

Tensor Tensor::transpose(){
	Tensor transpose = Tensor(dim2, dim1);
	for(int i = 0; i < dim1; i++){
		for(int j = 0; j < dim2; j++){
			transpose.insert(j, i, get(i, j));
		}

	}
	return transpose;
}


float Tensor::normEuclid(){
	float n = 0;
	for(int i = 0; i < dim1 * dim2; i++){
		n+=arr[i]*arr[i];
	}

	return sqrt(n);

}


float Tensor::getMax(){
	if(dim1 * dim2 == 0){
		return 0;
	}
	float max = arr[0];
	for(int i = 0; i < dim1*dim2; i++){
		max = std::max(arr[i], max);
	}
	return max;
}


float Tensor::costFunc(Tensor expected){
	float n = 0;
	int i;
	for(i = 0; i < dim1 * dim2; i++){
		n += (arr[i] - expected.arr[i])*(arr[i] - expected.arr[i]);
	}

	return n / (float)(2*i);
}

Tensor Tensor::sigmoidPrime(){
        Tensor newTens = Tensor(dim1, 1);
        for(int i = 0; i < dim1 * dim2; i++){
		//although i could do sigmoid * (1 - sigmoid)
		//This doesn't have a ton of new Tensors being made, only one
		//figured this is faster and I'm lazy
                newTens.insert(i, 0, 1 / (1 + exp(-arr[i])) * (1 - (1 + exp(-arr[i]))));
        }
        return newTens;
}

Tensor Tensor::inverse(){
	Tensor invTense = *this;

	return invTense;
}

float Tensor::trace(){
	float n = 0;
	for(int i = 0; i < dim1 && i < dim2; i++){
		n += get(i, i);
	}
	return n;

}

Tensor Tensor::operator -(){
        Tensor result = Tensor(dim1, dim2);
        for(int i = 0; i < dim1 * dim2; i++){
                result.arr[i] = -arr[i];
        }
        return result;
}
Tensor Tensor::operator +(const Tensor &tensor){
        return this->add(tensor);
}
Tensor Tensor::operator -(const Tensor &tensor){
        return this->minus(tensor);
}
Tensor Tensor::operator *(const Tensor &tensor){
        return this->stdMult(tensor);
}
Tensor Tensor::operator *(const float &val){
        return this->scalarMult(val);
}

bool Tensor::operator <(const Tensor &tensor){
	Tensor newTens = tensor;
        return (this->normEuclid()) < (newTens.normEuclid());
}
bool Tensor::operator >(const Tensor &tensor){
	Tensor newTens = tensor;
        return (this->normEuclid()) > (newTens.normEuclid());
}
bool Tensor::operator ==(const Tensor &tensor){
	Tensor newTens = tensor;
        return (this->normEuclid()) == (newTens.normEuclid());
}
bool Tensor::operator <=(const Tensor &tensor){
        Tensor newTens = tensor;
        return (this->normEuclid()) <= (newTens.normEuclid());
}
bool Tensor::operator >=(const Tensor &tensor){
        Tensor newTens = tensor;
        return (this->normEuclid()) >= (newTens.normEuclid());
}
Tensor::operator float(){
	return this->normEuclid();
}
Tensor Tensor::operator !(){
	return this->inverse();
}
Tensor Tensor::operator *(){
	return this->transpose();
}
float Tensor::operator ~(){
	return this->trace();
}
