#include <string>
#include <sstream>

#include "Matrix.hpp"

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

matlib::Matrix matlib::transpose(Matrix m){
	Matrix x;
	return x;
}
