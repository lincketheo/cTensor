#ifndef NETWORK_H
#define NETWORK_H
#include "tensor.h"
#include <string>


struct layer{
	int size;
	//need pointers because otherwise tensor.arr is overwritten
	//and i don't want to use vectors for speed's sake
	Tensor  inputs;
	Tensor  biases;
	Tensor  weights;
	//points to the next layer
	layer * next;
	layer * previous;
};

class Network{
	public:
		//input number of hidden layers - initializes hidden layer weights to random nums
		Network(int numIn, int numOut, int numHiddenLayers, int sizeHiddenLayers);
		~Network();
		Tensor propogateOneLayer();
		Tensor propogateNetwork(Tensor inputs);
		void printNetwork();
		void storeNetwork(std::string filename);
		void extractNetwork(std::string filename);
		void printNetworkSummary();
		void backPropogateRecurs(Tensor, Tensor, float);
		void backPropogate(Tensor, Tensor, float);

	private:
		layer * input;
		layer * output;
		//although we can get num in and out from head and tail,
		//this makes it convinient these are static
		int numberIn;
		int numberOut;
		int layers;
		int layersSize;
		
};

Tensor gradient(Tensor, layer*);








#endif
