#include <iostream>
#include <random>


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


int main(){

    
    for(int j = 0; j < 20; j++)
        std::cout<<RandomFloat(-2.0, 2.0)<<std::endl;
//        std::cout<<float(rand()) % 100<<std::endl;

    return 0;



}
