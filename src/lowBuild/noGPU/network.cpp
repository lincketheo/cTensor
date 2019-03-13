#include <iostream>
#include "head/tensor.hpp"
#include "head/network.hpp"


Network::Network(int numIn, int numOut, int numHiddenLayers, int sizeHiddenLayers){
	//initialize global variables
	numberIn = numIn;
	numberOut = numOut;
	layers = numHiddenLayers;
	layersSize = sizeHiddenLayers;
	
	//initialize layer
	input = new layer;
	input -> size = numIn;

	Tensor inweight = Tensor(sizeHiddenLayers, numIn, 1);
	input -> weights = inweight;
	//nothing to point to
	input -> previous = nullptr;

	layer * temp = input;
	layer * next = new layer;
	temp->next = next;


	for(int i = 0; i < numHiddenLayers - 1; i++){
		layer * next = new layer;

		temp->next = next;
		next->previous = temp;

		next -> size = sizeHiddenLayers;

		



		//Tensor bias = Tensor(sizeHiddenLayers, 1, 1);
		//Tensor weight = Tensor(sizeHiddenLayers, sizeHiddenLayers, 1);

		next -> size = sizeHiddenLayers;
		//next -> biases = bias;
		//next -> weights = weight;

	
		temp -> next = next;

		temp = temp->next;
	}

	temp = input->next;
	for(int i = 0; i < numHiddenLayers; i++){
		Tensor bias = Tensor(temp->next->size, 1, 1);
		Tensor weight = Tensor(temp->next->size, sizeHiddenLayer, 1);
		next->biases = bias;
		next->weights = weight;
	}

	Tensor outbias = Tensor(numOut, 1, 1);
	layer * next = new layer;
	next->size = numOut;
	next->biases = outbias;
	temp -> next = next;
	temp = temp->next;	

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

	Tensor weight = temp->weights;
	std::cout<<"Weights"<<std::endl;
	weight.print();
	std::cout<<std::endl;
        std::cout<<"------------------"<<std::endl;
        std::cout<<std::endl;
        temp = temp->next;

	while(temp->next != nullptr){
		
		Tensor bias = temp->biases;
		
		Tensor weight = temp->weights;

		Tensor transpBias = bias.transpose();
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
	Tensor bias = temp->biases;
	std::cout<<"Biases:"<<std::endl;
	Tensor transpBias = bias.transpose();
	transpBias.print();
        std::cout<<std::endl;
        std::cout<<"------------------"<<std::endl;
        std::cout<<std::endl;




}


Tensor propogateNetRecurs(layer * node, Tensor inputs){
	if(node->next == nullptr) return inputs;
	Tensor newTens = node->weights.stdMult(inputs).add(node->next->biases).sigmoid();
	std::cout<<"node time"<<std::endl;
	newTens.print();
        return propogateNetRecurs(node->next, newTens);
}


Tensor Network::propogateNetwork(Tensor inputs){
	return propogateNetRecurs(input, inputs);
}

void Network::printNetworkSummary(){
	std::cout<<"====================Network===================="<<std::endl;
	std::cout<<"Number of inputs: "<<numberIn<<std::endl;
	std::cout<<"Number of Outputs: "<<numberOut<<std::endl;
	std::cout<<"Number of hidden layers: "<<layers<<std::endl;
	std::cout<<"Size of hidden layers: "<<layersSize<<std::endl;
}

















































