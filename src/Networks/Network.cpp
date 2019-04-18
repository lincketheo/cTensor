#include <matLib.hpp>
#include <Network.hpp>
#include <iostream>

using namespace matlib;
using namespace NetworkLib;


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
	temp -> biases = Matrix(numOut, 1, 1);
	temp -> inputs = Matrix(temp->size, 1);
	temp -> next = nullptr;
	output = new layer;
	output = temp;

	//variable layer
	temp = temp -> previous;
	while(temp->previous != nullptr)
	{
		temp->weights = Matrix(temp->next->size, temp->size, 1);
		temp->biases = Matrix(temp->size, 1, 1);
		temp->inputs = Matrix(temp->size, 1);
		temp = temp->previous;
	}
	
	//temp is now input
	temp -> weights = Matrix(temp->next->size, temp->size, 1);
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

void Network::backPropogateRecurs(Matrix outputs, Matrix expected, float scalar){
	Matrix d_C = (outputs - expected);
	std::cout<<"here"<<std::endl;
	d_C.print();
	layer * last = output;
	last = last->previous;
	while(last != nullptr){
		std::cout<<1<<std::endl;
		d_C.print();
		d_C = gradient(d_C, last);
		std::cout<<2<<std::endl;
		d_C.print();
		last->next->biases = last->next->biases - d_C;
		last->weights = last->weights - (parMult(last->weights, d_C * (*last->inputs))) * scalar;
		last = last->previous;
		std::cout<<"askld"<<std::endl;
		d_C.print();
	}
}

void Network::backPropogate(Matrix inputs, Matrix expected, float scalar){
	Matrix outputs = propogateNetwork(inputs);
	backPropogateRecurs(outputs, expected, scalar);	
}
