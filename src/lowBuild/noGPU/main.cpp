#include <iostream>
#include "head/tensor.hpp"
#include "head/network.hpp"
#include <time.h>
#include <random>



int main(int argc, char const *argv[])
{
	Network mynet = Network(4, 5, 0, 6);

	mynet.printNetwork();


	return 0;
}
