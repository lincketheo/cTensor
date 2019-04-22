/**
    CS-11 Asn 2, Network.cpp
    Purpose: Network operations on a neural network 

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/
#include <matLib.hpp>       //matrix operations
#include <Network.hpp>      //main header
#include <iostream>         //printf std
#include <vector>           //vector
#include <math.h>           //sqrt

using namespace matlib;
using namespace NetworkLib;
using std::vector;
using std::cout;
using std::endl;


//================== Constructors ==================
//Standard sets everything to null
Network::Network()
{
    input = nullptr;
    output = nullptr;
    layersSize = 0;
    layers = 0;
    numberOut = 0;
    numberIn = 0;
}   

/**
    Encodes a Neural Network
    
    @param numIn number of inputs
    @param numOut number of outputs
    @param numHiddenLayers number of hidden layers
    @param sizeHiddenLayers size of each hidden layer

    @return a convolutional neural network with layer structs
*/
    
Network::Network(int numIn, int numOut, int numHiddenLayers, int sizeHiddenLayers)
{

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
	temp -> biases = Matrix(numOut, 1); 
	temp -> inputs = Matrix(temp->size, 1);
	temp -> next = nullptr;
	output = new layer;
	output = temp;

	//variable layer
	temp = temp -> previous;
	while(temp->previous != nullptr)
    {
		temp->weights = Matrix(temp->next->size, temp->size, 1 / sqrt(float(numIn)));
		temp->biases = Matrix(temp->size, 1);
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

//destroy a network
Network::~Network()
{
	while(input != NULL)
    {   
		layer * old = input;
		input = input -> next;
		delete old;
	}
}

//Prints the network (not to be confused with printNetworkSummary, this prints all the matrices)
void Network::printNetwork()
{
	cout<<"Input Layer: "<<endl;
	layer * temp = new layer;
	temp = input;

	Matrix weight = temp->weights;
	cout<<"Weights"<<endl;
	weight.print();
	cout<<endl;
        cout<<"------------------"<<endl;
        cout<<endl;
        temp = temp->next;

	while(temp->next != nullptr)
    {
		
		Matrix bias = temp->biases;
		
		Matrix weight = temp->weights;

		Matrix transpBias = *bias;
		cout<<"Biases:"<<endl;
		transpBias.print();
		
		cout<<"Weights:"<<endl;
		weight.print();

		cout<<endl;
		cout<<"------------------"<<endl;
		cout<<endl;
		temp = temp->next;
	}
	cout<<"Outputs"<<endl;
	Matrix bias = temp->biases;
	cout<<"Biases:"<<endl;
	Matrix transpBias = *bias;
	transpBias.print();
    cout<<endl;
    cout<<"------------------"<<endl;
    cout<<endl;
}


/**
    propogates a network recursively (helper function)
    
    @param node - the current node we are propogating in
    @param _inputs - the input to the layer we are on
    @return a matrix after propogating a single layer (eventually the final output
*/
Matrix propogateNetRecurs(layer * node, Matrix _inputs)
{
	node->inputs = _inputs;
	if(node->next == nullptr) return _inputs;
	Matrix newTens = ((node->weights * _inputs + node->next->biases)).relu();
	return propogateNetRecurs(node->next, newTens);
}

/**
    Runs a single network propogation

    @param inputs the matrix to input to the network
    @return a matrix after all transformations have been done
*/
Matrix Network::propogateNetwork(Matrix inputs)
{
	return propogateNetRecurs(input, inputs);
}

//prints a clean network summary including inputs, outputs, hidden layers and size hidden layers
void Network::printNetworkSummary()
{
	cout<<"====================Network===================="<<endl;
	cout<<"Number of inputs: "<<numberIn<<endl;
	cout<<"Number of Outputs: "<<numberOut<<endl;
	cout<<"Number of hidden layers: "<<layers<<endl;
	cout<<"Size of hidden layers: "<<layersSize<<endl;
	cout<<"==============================================="<<endl;
}

/**
    A back propogation algorithm for mmachine learning 

    @param outputs the output matrix for the neural network
    @param expected a collumn vector with 1 in the spot  we want the vector to be
    @param rate the rate of training

    @return void recursively updates weights and biases using the chain rule in calculus
*/
void Network::backPropogateRecurs(Matrix outputs, Matrix expected, float rate)
{
    //the propogating layer
    layer * temp = output->previous;

    //universal delta - propogates backwards
    Matrix del = parMult((outputs - expected), 
                (temp->weights * temp->inputs + temp->next->biases).reluPrime());

    //delGrad updated gradient for weights matrix
    Matrix delGrad = del * (*(temp->inputs));

    //update weights and biases
    temp->weights = temp->weights - ((parMult(temp->weights, delGrad)).scalarMult(rate));
    temp->next->biases = temp->next->biases - del.scalarMult(rate);
   
    temp = temp->previous;
    
    //loop backwards and do the same minus the initial del
    while(temp != nullptr)
    {
        //update del
        del = parMult(((*(temp->next->weights)) * del), 
                    (temp->weights * temp->inputs + temp->next->biases).reluPrime());

        //gradients
        Matrix delGrad = del * (*(temp->inputs));

        //update weights and biases
        temp->weights = temp->weights - ((parMult(temp->weights, delGrad)).scalarMult(rate));
        temp->next->biases = temp->next->biases - del.scalarMult(rate);
        temp = temp->previous;
    }
}



