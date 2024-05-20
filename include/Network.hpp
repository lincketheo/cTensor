#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <matLib.hpp>
#include <vector>

//uses matrices extensively
using namespace matlib;
using std::vector;

namespace NetworkLib{
	//A layer is a node to a linked list that points to the node before and after it (or nullptr)
	struct layer{
		int size;
		Matrix inputs;	  //backpropogation collects whatever was input to the layer
		Matrix biases;	  //the affine / additive matrix
		Matrix weights;	 //the transform matrix
		layer * next;	   //pointer to the next
		layer * previous;   //pointer to the previous
	};

	class Network{
		public:
			//main constructor - creates a neural network
			Network(int numIn, int numOut, int numHiddenLayers, int sizeHiddenLayers);
			Network();  //not used but initiallizes everything to null
			~Network(); //destructor
			Matrix propogateOneLayer();						 //propogates onlayer
			Matrix propogateNetwork(Matrix inputs);			 //propogates whole network
			void printNetwork();								//prints matrices in network
			void storeNetwork(std::string filename);			//stores network to a csv file
			void extractNetwork(std::string filename);		  //extracts csv network
			void printNetworkSummary();						 //prints a summary of the network
			void backPropogateRecurs(Matrix, Matrix, float);	//back propogation algorithm

		private:
			layer * input;	  //input layer (first)
			layer * output;	 //output layer (last)
			int numberIn;	   //number of inputs
			int numberOut;	  //number of outputs
			int layers;		 //number of layers
			int layersSize;	 //number of nodes per layer
	};
	//could add more  types of networks here
}

#endif
