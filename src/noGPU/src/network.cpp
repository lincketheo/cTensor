#include "tensor.h"
#include "network.h"
#include <iostream>


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
	temp -> biases = Tensor(numOut, 1, 1);
	temp -> next = nullptr;

	//variable layer
	temp = temp -> previous;
	while(temp->previous != nullptr)
	{
		temp->weights = Tensor(temp->next->size, temp->size, 1);
		temp->biases = Tensor(temp->size, 1, 1);
		temp = temp->previous;
	}
	
	//temp is now input
	temp -> weights = Tensor(temp->next->size, temp->size, 1);


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

		Tensor transpBias = *bias;
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
	Tensor transpBias = *bias;
	transpBias.print();
        std::cout<<std::endl;
        std::cout<<"------------------"<<std::endl;
        std::cout<<std::endl;

}


Tensor propogateNetRecurs(layer * node, Tensor inputs){
	//inputs is already transformed
	if(node->next == nullptr) return inputs;
	//could make this a nice two liner but nah
	Tensor newTens = ((node->weights * inputs) + (node->next->biases)).sigmoid();
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
	std::cout<<"==============================================="<<std::endl;
}

/*
Tensor Network::weightGradient(Network net, Tensor in, Tensor expc){
	
	Tensor propTens = net.propogateNetwork(in);
	if(expc.dim1 != propTens.dim1){
		printf("error in weightgradient\n");
		return propTens;
	}



}
*/




















