#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <matLib.hpp>
#include <Network.hpp>
#include <networkTrain.hpp>
#include <algorithm> 

using std::vector;
using std::string;
using std::cout;
using std::endl;
using matlib::Matrix;
using NetworkLib::Network;
using training::testElement;
using cv::Mat;
using namespace cv;

vector<testElement> training::uploadImages(int number, string filePath, string fileEnding, int maxIm){
    vector<cv::String> fn;
    cv::glob((filePath + string("*") + fileEnding).c_str(), fn, false);
    vector<testElement> matrices;
    size_t count = fn.size();
    for(size_t i = 0; i < count && i < maxIm; i++){
        testElement temp;
        Mat A = cv::imread(fn[i], 1);
//        cv::namedWindow("displaywindow", WINDOW_AUTOSIZE);
//        cv::imshow("displaywindow", A);
//        waitKey(0);
        Matrix B = Matrix(A.rows * A.cols, 1);
        for(int j = 0; j < A.rows * A.cols; j++)
            B.arr[j] = float(A.data[j] / 255.0);
        temp.mat = B;
        temp.label = number;
//        std::cout<<number<<std::endl;
        matrices.push_back(temp);
    }
    return matrices;
}

vector<testElement> training::uploadAllImages(string basePath, const char ** fileNames, int * labels, int numLabels, string fileEnding, int maxIm){
    vector<testElement> main;
    for(int i = 0; i < numLabels; i++){
        string file = basePath + string("/") + fileNames[i] + string("/");
        vector<testElement> b = uploadImages(labels[i], file, fileEnding, maxIm);
        main.insert(main.end(), b.begin(), b.end());
    }
    std::random_shuffle(main.begin(), main.end());
    return main;
}

int training::getNumOut(vector<testElement> elements){
    int max = 0; //assume labels are greater than 0 otherwise INT_MIN
    for(int i = 0; i < elements.size(); i++)
        if(elements[i].label > max)max = elements[i].label;
    return max + 1;
}

int training::getNumIn(vector<testElement> elements){
    return elements[0].mat.dim1;
}

Matrix training::createOutput(int size, int label){
    Matrix a(size, 1);
    a.insert(0, 0, 0);
    a.insert(label, 0, 1);
    return a;
}

Network training::trainDataSet(vector<testElement> testSet, int nHL, int sHL, float scalar){
    int numIn = getNumIn(testSet);
    int numOut = getNumOut(testSet);
//    std::cout<<numIn<<" "<<numOut<<std::endl;
    Network main(numIn, numOut, nHL, sHL);
//    main.printNetwork();
    for(int i = 0; i < testSet.size(); i++){
        float average1 = 0;
        float average2 = 0;
        Matrix expected = createOutput(numOut, testSet[i].label);
//        std::cout<<testSet[i].label<<std::endl;
        Matrix out = main.propogateNetwork(testSet[i].mat);
        main.backPropogateRecurs(out, expected, scalar / (i + 1));
        Matrix out2 = main.propogateNetwork(testSet[i].mat);
        Matrix t1 = expected - out;
        Matrix t2 = expected - out2;
        for(int i = 0; i < 10; i++){
            average1 += t1.get(i, 0);
            average2 += t2.get(i, 0);
        }
        std::cout<<average1 - average2<<std::endl;
    }
//    main.printNetwork();
    return main;
}

void training::runOnMatrix(Network net, Matrix mat, int expected){
    Matrix out = net.propogateNetwork(mat);
    //net.printNetwork();    
    Matrix expect = createOutput(out.dim1, expected);
    
    //printf("Input\n");
   // mat.print();
    printf("Expected\n");
    expect.print();
    printf("Output\n");
    out.print();
}

