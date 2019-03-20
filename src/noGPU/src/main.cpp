#include <iostream>
#include "tensor.h"
#include "network.h"

#define PI 3.14169265358979323846264

int main(int argc, char const *argv[])
{
	

	Tensor t1(4, 4, 1);
	Tensor t2(4, 1);
	Tensor t3(4, 1, 1);
	Tensor t4(4, 1, 1);

	((t1 * t3).sigmoid() + t3).print();
	Tensor t = t3;
	t2.print();
	t3.print();
	t4.print();
	t1 = weightGrad(t1, t2, t, t4);
	t = t3;
	t2.print();
	t3.print();
	t4.print();
        t1 = weightGrad(t1, t2, t3, t4);




	/*		
	Tensor t9(4, 1, 1);
	Tensor t10(4, 1, 1);
	Tensor t11(10, 4);

	t9.print();
	t10.print();
	
	parMult(t9, t10).print();	


	Tensor t1(2, 2, 1);
	Tensor t2(2, 2, 1);
	std::cout<<"t1"<<std::endl;
	t1.print();
	std::cout<<"t2"<<std::endl;
	t2.print();

	Tensor t3 = t1 * t2;
	std::cout<<"t1 * t2"<<std::endl;
	t3.print();
	t3 = t2 * t1;
	std::cout<<"t2 * t1 = t3"<<std::endl;
	t3.print();	
	
	if(t1 > t2){
		std::cout<<"t1 > t2"<<std::endl;
	}else{
		std::cout<<"t2 > t1"<<std::endl;
	}

	std::cout<<std::endl;
	std::cout<<"Computed with the euclidean / frobenius norm"<<std::endl;
	std::cout<<"Pretty cool, I can type cast tensors"<<std::endl;
	std::cout<<"float(t1) = "<<float(t1)<<std::endl;
	std::cout<<"float(t2) = "<<float(t2)<<std::endl;
	std::cout<<"float(t3) = "<<float(t3)<<std::endl;
	std::cout<<"as well as type cast it to a double, or int"<<std::endl;
	std::cout<<"int(t1) = "<<int(t1)<<std::endl;
	std::cout<<"int(t2) = "<<int(t2)<<std::endl;
	std::cout<<"int(t3) = "<<int(t3)<<std::endl;
	std::cout<<"this means you can pass tensors to functions that require floats or ints"<<std::endl;
	Tensor t4(3, 1, 1);
	std::cout<<"Transposes, all you do is type *tensor"<<std::endl;
	std::cout<<"t4 = "<<std::endl;
	t4.print();
	std::cout<<"*t4 = "<<std::endl;
	(*t4).print();
	std::cout<<"and finally, the trace, tr(t1) = ~t1 = "<<~t1<<std::endl;

	*/


	
	
	/*	
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
	*/
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
