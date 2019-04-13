#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Matrix.hpp"

using namespace matlib;

matlib::Matrix::Matrix(){}

matlib::Matrix::Matrix(std::string str){
	std::stringstream ss;
	ss << str;
	std::string row;
	while(getline(ss, row, ';')){
		std::stringstream ssrow;
		ssrow << row;
		std::string element;
		int curr;
		matlib::element* prev;

		while(getline(ssrow, element, ' ')){
			
		}

		
	}
}

matlib::Matrix::~Matrix(){

}

#include <cmath>
#include <random>
#include <iostream>
#include "tensor.h"
#include <stdexcept>

//initializes tensor to a 2 x 2 zero matrix
Matrix::Matrix(int d1, int d2){
    rows = d1;
    cols = d2;
    for(int i = 0; i < dim1 && i < dim2; i++){
        element v;
        v.row = i + 1;
        v.col = i + 1;
        v.val = 1;
        elements.push_back(v);
    }
}


Matrix::Matrix(int _dim1, int _dim2, int desiredMax){
	rows = _dim1;
	rows = _dim2;
	std::random_device rd;
	float ratio = ((float)desiredMax) / rd.max();
	for(int i = 0; i < dim1; i++){
        for(int j = 0; j < _dim2; j++){
            element v;
            v.row = i;
            v.col = j;
            v.val = ratio * rd();
            elements.push_back(v);
        }
	}
}

//prints tensor
void Tensor::print(){
	std::cout<<std::endl;
	for(int i = 0; i < dim1; i ++){
		for(int j = 0; j < dim2; j++){
			printf("%.3f ", arr[(i*dim2)+j]);
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
	if(dim1 != tensor.dim1 || dim2 != tensor.dim2){
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
        if(dim1 != tensor.dim1 || dim2 != tensor.dim2){
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
        if(dim1 != tensor.dim1 || dim2 != tensor.dim2){
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
	Tensor newTensor = Tensor(dim1, tensor.dim2);
	if(dim2 != tensor.dim1){
		throw std::invalid_argument("dim missmatch");
	}
	for(int i = 0; i < dim1; i++){
		for(int j = 0; j < tensor.dim2; j++){
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

                newTens.insert(i, 0, (1 / (1 + exp(-arr[i]))) * (1 - (1 / (1 + exp(-arr[i])))));
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
Tensor rotate(Tensor t1, float theta, int x, int y)
{
        Tensor newTens(t1.dim1, t1.dim1);
        newTens.insert(x, x, cos(theta));
        newTens.insert(y, x, sin(theta));
        newTens.insert(y, y, cos(theta));
        newTens.insert(x, y, -sin(theta));
        return newTens * t1;

}

Tensor parMult(Tensor t, Tensor t2){
	Tensor t1(t.dim1, t.dim2);
        if(t1.dim1 != t2.dim1 || t1.dim2 != t2.dim2){
                throw std::invalid_argument("dim missmatch");
        }
        for(int i = 0; i < t1.dim1 * t1.dim2; i++){
                t1.arr[i] = t.arr[i] * t2.arr[i];
        }

        return t1;
}

Tensor parAdd(Tensor t, Tensor t2){
	Tensor t1 = t;
	if(t1.dim1 != t2.dim1){
		throw std::invalid_argument("dim missmatch");
	}
	for(int i = 0; i < t2.dim1; i ++){
		for(int j = 0; j < t1.dim2; j++){
			t1.insert(i, j, t1.get(i, j) + t2.get(i, 1));
		}
	}
	return t1;

}

Tensor parSqr(Tensor t){
	Tensor t1 = t;
        for(int i = 0; i < t1.dim1 * t1.dim2; i++){
                t1.arr[i] = t1.arr[i] * t1.arr[i];
        }
        return t1;
}

Tensor weightGrad(Tensor weight, Tensor expc, Tensor in, Tensor bias){
	Tensor t1 = (parAdd(weight * in, bias)).sigmoid() - expc;
	Tensor t2 = (weight * in + bias).sigmoidPrime();
	Tensor t3 = parMult(t1, t2);
	Tensor t4 = parMult(in, t3);
	weight = weight - (t4 * (*in));
	
	printf("round 2\n");
        parSqr((weight * in + bias).sigmoid() - expc).print();

	return weight;
}


Tensor Tensor::getCol(int col){
    Tensor newTens(dim1, 1);
    for(int i = 0; i < dim1; i++){
        newTens.insert(i, 0, get(col, i));
    }
    return newTens;
}

Tensor Tensor::getRow(int row){
    Tensor newTens(1, dim2);
    for(int i = 0; i < dim2; i++){
        newTens.insert(0, i, get(i, row));
    }
    return newTens;
}

void Tensor::replaceRow(int row, Tensor t){
    for(int i = 0; i < dim2; i++){
        insert(row, i, t.get(0, i));        
    }
}
void Tensor::replaceCol(int col, Tensor t){
    for(int i = 0; i < dim1; i++){
        insert(i, col, t.get(i, 0));
    }
}

void Tensor::swapRow(int r1, int r2){
    Tensor temp = getRow(r1);
    replaceRow(r1, getRow(r2));
    replaceRow(r2, temp);
}

void Tensor::swapCol(int c1, int c2){
    Tensor temp = getCol(c1);
    replaceCol(c1, getCol(c2));
    replaceCol(c2, temp);
}

/*
void Tensor::rref(){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            if(get(0, 0) == 0 && dim1 > 1)swapRow(0, 1);
            
        }
    }


    if(get(0, 0) == 0 && dim1 > 1){
        swapRow(0, 1);
    }
    for(int i = 0; i < 


}

*/









/*
Tensor biasGrad(Tensor t1, Tensor expc){
        return 2 * parMult(((weight * in).sigmoid() + bias), (weight * in + bias).sigmoidPrime());

}
*/

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
matlib::Matrix matlib::transpose(Matrix m){
	Matrix x;
    //noice
	return x;
}
