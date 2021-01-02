/**
    CS-11 Asn 2, CNN.cpp
    Purpose: CNN operations on a neural network 

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/
#include "CNN.hpp"      //main header

using namespace matlib;
using namespace NetworkLib;
using std::vector;
using std::cout;
using std::endl;

//================== Constructors ==================
//Standard sets everything to null
CNN::CNN()
{
    input = nullptr;
    output = nullptr;
}   

/**
    Encodes a Neural CNN
    
    @param numIn number of inputs
    @param numOut number of outputs
    @param numHiddenLayers number of hidden layers
    @param sizeHiddenLayers size of each hidden layer

    @return a convolutional neural network with layer structs
*/
    
CNN::CNN(const std::vector<int> _layer_sizes)
	: layer_sizes(_layer_sizes)
{
	if(layers() < 2){
		throw std::invalid_argument("Need at least 2 layers");
	}

	//Initialize input
	input = new layer;
	input -> size = num_in();
	input -> previous = nullptr;

	//variable layer
	layer * temp = new layer;
	input -> next = temp;
	temp -> previous = input;	
	
	//go forward to assign sizes and go backwards to assign weights biases
	for(int i = 0; i < layers() - 2; i++)
    {
		temp->size = hidden_layer_size(i);
		layer * next = new layer;
		temp -> next = next;
		next -> previous = temp;
		temp = temp -> next;
	}

	//output layer
	temp -> size = num_out();
	temp -> biases = std::make_unique<Matrix>(temp->size, 1); 
	temp -> inputs = std::make_unique<Matrix>(temp->size, 1);
	temp -> next = nullptr;
	output = new layer;
	output = temp;

	//variable layer
	temp = temp -> previous;
	while(temp->previous != nullptr)
    {
		temp->weights = std::make_unique<Matrix>(temp->next->size, temp->size, 1 / sqrt(float(num_in())));
		temp->biases = std::make_unique<Matrix>(temp->size, 1);
		temp->inputs = std::make_unique<Matrix>(temp->size, 1);
		temp = temp->previous;
	}
	
	//temp is now input
	temp -> weights = std::make_unique<Matrix>(temp->next->size, temp->size, 1 / sqrt(float(num_in())));
	temp -> inputs = std::make_unique<Matrix>(temp->size, 1);
}

//destroy a network
CNN::~CNN()
{
	while(input != NULL)
    {   
		layer * old = input;
		input = input -> next;
		delete old;
	}
}

void CNN::print_inputs(){
	layer* temp = new layer;
	temp = input;
	while(temp != nullptr){
		temp->inputs->print();
		temp = temp->next;
	}
}

//Prints the network (not to be confused with printCNNSummary, this prints all the matrices)
void CNN::print_network()
{
	cout<<"Input Layer: "<<endl;
	layer * temp = new layer;
	temp = input;

	// This copies - print network doesn't need to be optimized
	Matrix weight = *temp->weights;
	cout<<"Weights"<<endl;
	weight.print();
	cout<<endl;
        cout<<"------------------"<<endl;
        cout<<endl;
        temp = temp->next;

	while(temp->next != nullptr)
    {
		// Again - all of these are copies - no need to optimize here yet
		Matrix bias = *temp->biases;
		Matrix weight = *temp->weights;

		cout<<"Biases:"<<endl;
		bias.transpose().print();
		
		cout<<"Weights:"<<endl;
		weight.print();

		cout<<endl;
		cout<<"------------------"<<endl;
		cout<<endl;
		temp = temp->next;
	}
	cout<<"Outputs"<<endl;
	Matrix bias = *temp->biases;
	cout<<"Biases:"<<endl;
	bias.transpose().print();
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
void propogate_net_recurs(layer * node)
{
	// If node is output - break
	if(node->next == nullptr) return;

	// output = next inputs = weights * input + next bias
	*node->next->inputs = *(node->weights) * *(node->inputs) + *(node->next->biases);
	return propogate_net_recurs(node->next);
}

/**
    Runs a single network propogation

    @param inputs the matrix to input to the network
*/
void CNN::propogate_network(std::unique_ptr<Matrix> inputs)
{
	input->inputs = std::move(inputs);
	propogate_net_recurs(input);
}

//prints a clean network summary including inputs, outputs, hidden layers and size hidden layers
void CNN::print_network_summary()
{
	cout<<"====================CNN===================="<<endl;
	for(int i = 0; i < layers(); ++i)
		cout<<"Layer: "<<i<<" Size: "<<layer_sizes[i]<<endl;
	cout<<"==============================================="<<endl;
}

/**
    A back propogation algorithm for mmachine learning 

    @param outputs the output matrix for the neural network
    @param expected a collumn vector with 1 in the spot  we want the vector to be
    @param rate the rate of training

    @return void recursively updates weights and biases using the chain rule in calculus
*/
void CNN::back_propogate_network(const Matrix& expected, float rate)
{
    //the propogating layer
    layer * temp = output->previous;

	Matrix del = *output->inputs - expected;
	del.par_mult(*temp->weights * *temp->inputs + *temp->next->biases);
	del.relu_prime();

    //delGrad updated gradient for weights matrix
	Matrix delGrad;
	delGrad = del * temp->inputs->transpose();
	delGrad.par_mult(*temp->weights);

	*temp->weights = *temp->weights - delGrad * rate;
	*temp->next->biases = *temp->next->biases - del * rate;

    temp = temp->previous;
    
    //loop backwards and do the same minus the initial del
    while(temp != nullptr)
    {
        //update del
		del = *temp->next->weights * del;
		del.par_mult(*temp->weights * *temp->inputs + *temp->next->biases);
		del.relu_prime();

        //gradients
        delGrad = del * temp->inputs->transpose();
		delGrad.par_mult(*temp->weights);

        //update weights and biases
		*temp->weights = *temp->weights - delGrad * rate;
		*temp->next->biases = *temp->next->biases - del * rate;

		temp = temp->previous;
    }
}



