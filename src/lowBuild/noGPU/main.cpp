#include <iostream>
#include "head/tensor.hpp"
#include "head/network.hpp"
#include <time.h>
#include <random>



int main(int argc, char const *argv[])
{
	clock_t t;
	Network mynet = Network(4, 10, 3, 4);
	t = clock();
	t = clock() - t;
	printf("Execution time: %f second\n", (float)t / CLOCKS_PER_SEC);

	mynet.printNetwork();
	//mynet.printNetworkSummary();
	Tensor myTens = Tensor(4, 1, 3);

	t = clock() - t;
	printf("Execution time: %f second\n",(float)t / CLOCKS_PER_SEC);

	//myTens.print();
	//std::cout<<"input="<<std::endl;
	//myTens.print();
	
	std::cout<<"outputs="<<std::endl;	
	
	Tensor propTens = mynet.propogateNetwork(myTens);
	//propTens.print();
	t = clock() - t;
	
	propTens.print();

	printf("Execution time: %f seconds\n", ((float)t) / CLOCKS_PER_SEC);
	
	std::cout<<propTens.normEuclid()<<std::endl;
	std::cout<<propTens.getMax()<<std::endl;

	return 0;
}
