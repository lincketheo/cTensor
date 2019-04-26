#include <iostream>
#include <matLib.hpp>
#include <networkTrain.hpp>
#include <vector>
#include <Network.hpp>
#include <constants.hpp>


using namespace matlib;
using namespace NetworkLib;
using namespace training;
using std::vector;
using std::string;




int main(int argc, char ** argv){

    srand((unsigned int)time(NULL));

    const char * fileNames[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int labels[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 

    trainingSet testing = uploadAllImages(fileBaseCONSTANT, fileNames, labels, 10, "jpg", 10000);

    int nHL[100] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int sHL[100] = {600, 650, 550, 400, 400, 100, 100, 100, 50, 50, 50, 200, 200, 200};
    float rate[100] = {.009, .009, .009, .007, .008, .009, .007, .008, .009, .007, .008, .009, .007};
    trainingSet testing2 = uploadAllImages(fileBaseTestCONSTANT, fileNames, labels, 10, "jpg", 20);


    for(int i = 0; i < 15; i++){
        Network * temp = trainDataSet(testing, nHL[i], sHL[i], rate[i]);
        float result = testOnTestSet(testing2, temp); 
        std::cout<<result<<std::endl;
    }
    return 0;
}

