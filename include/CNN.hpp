#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <memory>

#include "Matrix.hpp"

//uses matrices extensively
using namespace matlib;
using std::vector;

namespace NetworkLib{

	//A layer is a node to a linked list that points to the node before and after it (or nullptr)
	struct layer{
		int size; 			// Number of Inputs

		std::unique_ptr<Matrix> biases;	  	//the affine / additive matrix
		std::unique_ptr<Matrix> weights;	 	//the transform matrix

		layer * next;	   	//pointer to the next
		layer * previous;   //pointer to the previous

		// Forward Propigation Memory
		// Input to the output layer is the output
		std::unique_ptr<Matrix> inputs;	  	//backpropogation collects whatever was input to the layer
	};

	class CNN{
		public:

			CNN();  //not used but initiallizes everything to null

			/**
			 * @brief Constructor - creates a CNN
			 * 
			 * @param layer_sizes Sizes of each layer (including input and output, so there should
			 * be a minimum of 2)
			 */
			CNN(const std::vector<int> _layer_sizes);

			/**
			 * Default destructor
			 */
			~CNN();

		public:
			void propogate_network(std::unique_ptr<Matrix> inputs);
			void back_propogate_network(const Matrix& inputs, float rate);
			void print_network();
			void print_inputs();
			void print_network_summary();

			void store_network(const std::string& filename);
			void extract_network(const std::string& filename);


		protected:
			int layers(){return layer_sizes.size();}
			int hidden_layers(){return layer_sizes.size() - 2;}
			int hidden_layer_size(int i){return layer_sizes[i + 1];}
			int num_in(){return layer_sizes[0];}
			int num_out(){return layer_sizes.back();}

		private:
			layer * input;	  //input layer (first)
			layer * output;	 //output layer (last)
			std::vector<int> layer_sizes;
	};
}

#endif
