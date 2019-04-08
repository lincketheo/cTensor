#include <iostream>
#include "tensor.h"
#include "network.h"

#define PI 3.14169265358979323846264

int main(int argc, char const *argv[])
{
	/*
	Network mynet = Network(5, 10, 2, 10);

	Tensor inputTens = Tensor(5, 1, 1);
	Tensor expected = Tensor(10, 1);
	expected.insert(0, 0, 0);
	expected.insert(2, 0, 1);
	
	Tensor t1 = mynet.propogateNetwork(inputTens);
	
	for(int i = 0; i < 10; i++){
		mynet.backPropogate(inputTens, expected, 1);
	}
	Tensor t2 = mynet.propogateNetwork(inputTens);

	t1.print();
	t2.print();
	expected.print();
    */
	
	//RUN THIS CODE TO SEE HOW NETWORK WORKS
	//network(number inputs, number outputs, number hidden layers, size hidden layers)
	Network mynet = Network(5, 10, 2, 10);
	mynet.printNetworkSummary();
	mynet.printNetwork();

	//Tensor(cols, rows, maximum random val)
	//NOTE: network doesn't check for matching rows / cols	
	Tensor inputTens = Tensor(5, 1 , 1);
	Tensor propTens = mynet.propogateNetwork(inputTens);
	std::cout<<"Input tensor"<<std::endl<<"========================================"<<std::endl;
	inputTens.print();
	std::cout<<"========================================"<<std::endl;
        std::cout<<"Output tensor"<<std::endl<<"========================================"<<std::endl;
	propTens.print();
	std::cout<<"========================================"<<std::endl;
	/*
	//PUSH THAT BABY TO ITS LIMITS HONEY!!
	//(we're talking 5000 * 1000 matrices as hidden weights, this'll absolutely return 1)
	Network mynet = Network(5000, 10, 9, 1000);
	mynet.printNetworkSummary();

	Tensor inputTens = Tensor(5000, 1, 1);
	Tensor propTens = mynet.propogateNetwork(inputTens);
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Output tensor"<<std::endl<<"========================================"<<std::endl;
        propTens.print();
        std::cout<<"========================================"<<std::endl;
	*/

	return 0;
}
