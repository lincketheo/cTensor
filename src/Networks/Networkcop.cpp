#include <matLib.hpp>
#include <Network.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace matlib;
using namespace NetworkLib;
using std::vector;


//================== Constructors ==================
/**
    Encodes a Neural Network
    
    @param numIn number of inputs
    @param numOut number of outputs
    @param numHiddenLayers number of hidden layers
    @param sizeHiddenLayers size of each hidden layer

    @return a convolutional neural network with layer structs
*/
    
Network::Network(int numIn, int numOut, int numHiddenLayers, int sizeHiddenLayers){

	//Initialize input
	input = new layer;
	input -> size = numIn;
	input -> previous = nullptr;

	//variable layer
	layer * temp = new layer;
	input -> next = temp;
	temp -> previous = input;	
	
	//go forward to assign sizes and go backwards to assign weights biases
	for(int i = 0; i < numHiddenLayers; i++)
	{
		temp->size = sizeHiddenLayers;
		layer * next = new layer;
		temp -> next = next;
		next -> previous = temp;
		temp = temp -> next;
	}

	//output layer
	temp -> size = numOut;
	temp -> biases = Matrix(numOut, 1, 1 / sqrt(float(numIn)));
	temp -> inputs = Matrix(temp->size, 1);
	temp -> next = nullptr;
	output = new layer;
	output = temp;

	//variable layer
	temp = temp -> previous;
	while(temp->previous != nullptr)
	{
		temp->weights = Matrix(temp->next->size, temp->size, 1 / sqrt(float(numIn)));
		temp->biases = Matrix(temp->size, 1, 1 / sqrt(float(numIn)));
		temp->inputs = Matrix(temp->size, 1);
		temp = temp->previous;
	}
	
	//temp is now input
	temp -> weights = Matrix(temp->next->size, temp->size, 1 / sqrt(float(numIn)));
	temp -> inputs = Matrix(temp->size, 1);

	numberIn = numIn;
	numberOut = numOut;
	layers = numHiddenLayers;
	layersSize = sizeHiddenLayers;
}

Network::~Network(){
	while(input != NULL){
		layer * old = input;
		input = input -> next;
		delete old;
	}
}

void Network::printNetwork(){
	std::cout<<"Input Layer: "<<std::endl;
	layer * temp = new layer;
	temp = input;

	Matrix weight = temp->weights;
	std::cout<<"Weights"<<std::endl;
	weight.print();
	std::cout<<std::endl;
        std::cout<<"------------------"<<std::endl;
        std::cout<<std::endl;
        temp = temp->next;

	while(temp->next != nullptr){
		
		Matrix bias = temp->biases;
		
		Matrix weight = temp->weights;

		Matrix transpBias = *bias;
		std::cout<<"Biases:"<<std::endl;
		transpBias.print();
		
		std::cout<<"Weights:"<<std::endl;
		weight.print();

		std::cout<<std::endl;
		std::cout<<"------------------"<<std::endl;
		std::cout<<std::endl;
		temp = temp->next;
	}
	std::cout<<"Outputs"<<std::endl;
	Matrix bias = temp->biases;
	std::cout<<"Biases:"<<std::endl;
	Matrix transpBias = *bias;
	transpBias.print();
        std::cout<<std::endl;
        std::cout<<"------------------"<<std::endl;
        std::cout<<std::endl;
}


Matrix propogateNetRecurs(layer * node, Matrix _inputs){
	node->inputs = _inputs;
	if(node->next == nullptr) return _inputs;
	Matrix newTens = ((node->weights * _inputs) + (node->next->biases)).sigmoid();
	return propogateNetRecurs(node->next, newTens);
}

Matrix Network::propogateNetwork(Matrix inputs){
	return propogateNetRecurs(input, inputs);
}

void Network::printNetworkSummary(){
	std::cout<<"====================Network===================="<<std::endl;
	std::cout<<"Number of inputs: "<<numberIn<<std::endl;
	std::cout<<"Number of Outputs: "<<numberOut<<std::endl;
	std::cout<<"Number of hidden layers: "<<layers<<std::endl;
	std::cout<<"Size of hidden layers: "<<layersSize<<std::endl;
	std::cout<<"==============================================="<<std::endl;
}

Matrix gradient(Matrix previous, layer * layer){
	Matrix t1 = parMult(previous, (layer->weights * layer->inputs + layer->next->biases).sigmoidPrime());
	std::cout<<"this equatoianfkjsdnfkjndsf"<<std::endl;
	previous.print();
	(layer->weights * layer->inputs + layer->next->biases).print();
	(layer->weights * layer->inputs + layer->next->biases).sigmoidPrime().print();
	t1.print();

	return t1;
}

void Network::backPropogateRecurs(Matrix outputs, Matrix expected, float rate){
//    printNetwork();
    layer * temp = output->previous;
    
  //  output->inputs.print();
  //  outputs.print();
    
    Matrix del = parMult((outputs - expected), 
                (temp->weights * temp->inputs + temp->next->biases).sigmoidPrime());
//    del.print();
    Matrix delGrad = del * (*(temp->inputs));
    
    temp->weights = temp->weights - ((parMult(temp->weights, delGrad)).scalarMult(rate));
    temp->next->biases = temp->next->biases - ((parMult(temp->next->biases, del)).scalarMult(rate));// / i));
    temp = temp->previous;
    while(temp != nullptr){
        del = parMult((*(temp->next->weights) * del), 
                    (temp->weights * temp->inputs + temp->next->biases).sigmoidPrime());


        Matrix delGrad = del * (*(temp->inputs));
//        delGrad.print();
        temp->weights = temp->weights - ((parMult(temp->weights, delGrad)).scalarMult(rate));
        
    
        temp->next->biases = temp->next->biases - ((parMult(temp->next->biases, del)).scalarMult(rate));// / i));
        temp = temp->previous;
    }
//    printNetwork();
}


Network NetworkLib::trainNetwork(int numHidden, int scalar, int sizeHidden, int numIn, int numOut, vector<Matrix> inputs, vector<int> labels){
    Network main(numIn, numOut, numHidden, sizeHidden);
    for(int i = 0; i < inputs.size(); i++){
        std::cout<<"here"<<std::endl;
        Matrix expected(numOut, 1);
        expected.insert(0, 0, 0);
        expected.insert(labels[i], 0, 1);
        Matrix out = main.propogateNetwork(inputs[i]);
        main.backPropogateRecurs(out, expected, scalar);
    }

    return main;
}
