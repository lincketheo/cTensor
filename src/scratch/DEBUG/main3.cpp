#include <iostream>
#include <matLib.hpp>
#include <networkTrain.hpp>
#include <vector>
#include <Network.hpp>


using namespace matlib;
using namespace NetworkLib;
using namespace training;
using std::vector;
using std::string;

const string fileBase = "/home/theo/Documents/projects/math/tensorFlow/cTensor/src/Data/images/mnist_jpgfiles/train";
const string fileBaseTest = "/home/theo/Documents/projects/math/tensorFlow/cTensor/src/Data/images/mnist_jpgfiles/test";

int main(int argc, char ** argv){

    srand((unsigned int)time(NULL));

    const char * fileNames[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int labels[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 

    trainingSet testing = uploadAllImages(fileBase, fileNames, labels, 10, "jpg", 1000);
        for(int i = 0; i < testing.files.size(); i++){
            std::cout<<testing.files[i].file<<std::endl;
        }


    int a = std::stoi(argv[1]);
    int b = std::stoi(argv[2]);
    float c = std::stof(argv[3]);
    
    Network myNet = trainDataSet(testing, a, b, c);

    runOnMatrix("/home/theo/Documents/projects/math/tensorFlow/cTensor/src/Data/images/mnist_jpgfiles/train/4/mnist_4_520.jpg", myNet, 4);
    runOnMatrix("/home/theo/Documents/projects/math/tensorFlow/cTensor/src/Data/images/mnist_jpgfiles/train/5/mnist_5_488.jpg", myNet, 5);
   /* 
    trainingSet testing2 = uploadAllImages(fileBaseTest, fileNames, labels, 10, "jpg", 100);


        for(int i = 0; i < testing2.files.size(); i++){
            std::cout<<testing2.files[i].file<<std::endl;
        }


    float result = testOnTestSet(testing2, myNet);   
    std::cout<<result<<std::endl;
 

    return 0;
*/
}








































/*


vector<testElements> uploadImages(std::string filePath, int numberOfEach){
    vector<vector<Matrix>> vals;
    for(int i = 0; i < 10; i++){
        vals.push_back(loadTestImages(filePath, i, numberOfEach));
    }
    return vals; 
}

vector<testElement> loadTestImages(std::string testFilePath, int number, int numImages){
    vector<testElement> matrices;
    char * filepath = new char[200];
    for(int j = 1; j < numImages + 1; j++){
        //printf("%s/%i/mnist_%i_%i.jpg", testFilePath.c_str(), number, number, j);
        Matrix A(28 * 28, 1);
        sprintf(filepath, "%s/%i/mnist_%i_%i.jpg", testFilePath.c_str(), number, number, j);
        Mat image = imread(filepath, 1); 
        printf("Loading Image: %i/mnist_%i_%i.jpg\n", number, number, j);
        for(int i = 0; i < 28 * 28; i++){
            A.arr[i] = (float)image.data[i];
        }
        testElement elements;
        elements.element = A;
        elements.label = number;
        matrices.elements;
    }
    return matrices;
}

void displayImage(std::string filename, int dataVal, int number);

*/
/*

    Matrix A(28 * 28, 1);
    Mat D = imread("Data/mnist_9_123.jpg", 1);
    if(!D.data){
        printf("No image\n");
        return -1;
    } 
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", D);

    waitKey(0);
    for(int i = 0; i < 28 * 28; i++){
        A.arr[i] = D.data[i];
    }
    
    A.print();
  */  
    //return 0;

//}

/*
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    //if ( argc != 2 )
    //{
    //    printf("usage: DisplayImage.out <Image_Path>\n");
    //    return -1;
    //}

    //Mat image;
    //image = imread( argv[1], 1);
    //std::cout<<image.row(1)<<std::endl;
    Mat D(2,9, 1, Scalar(0,0,255));
    std::cout<<D<<std::endl;
    std::cout<<D.dims<<std::endl;
    for(int i = 0; i < D.rows * D.cols; i++){
       std::cout<<(int)D.data[i]<<std::endl;
    }
    std::cout<<D.rows<<std::endl;

    //if ( !image.data )
    //{
    //    printf("No image data \n");
    //    return -1;
    //}


    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", image);

    //waitKey(0);

    return 0;
}
*/
