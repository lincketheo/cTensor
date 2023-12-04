#include <iostream>
#include <random>
#include <vector>
#include "Matrix.hpp"
#include "Network.hpp"
#include "training.hpp"
#include <algorithm>

/**
    train uploads jpg png and any opencv allowed image
    assumess the following directory structure

    basePath
        trainingdirectory1
            image1
            image2
            ...
        trainingdirectory2
            image1
            image2
            ...
        ...

    assumptions:
    
    all images in trainingdirector_x have the same label
    all images are the same size *note below

    none of  these need to follow any format other than the standard linux file system
    The program uses glob which puts all the file name strings in a given directory
    Problems you may encounter include a corrupt / false image or a non image, 
    however glob does check wether the <fileEnding> string is on the back of the file
    
    *It is possible  to filter through this in some ways, but I did not
    A possible way to combat this is to limit the amount of  data being transfered to our input
    matrix
    
    Finally, all the greeting_ascii labels don't necessarily have to be numbers,
    for example, you could have labels for clothing or faces, but the program takes in a number
    so your best option is to assign a number to a type (1 gets dress, 2 gets shoe etc.)
*/



/**
    upload Images grabs all file names ending in fileEnding in a file path

    @param number the  number the image represents or the label
    @param filePath the base path to the main file
    @param fileEnding jpg png etc
    @param maxIm number of images we want to extract 
    (or the number of images in the folder if maxIm is to large
    
    @return a vector cv strings to each file
*/
vector<trainElem> uploadImages(
        int number, const std::string &filePath,
        const std::string &fileEnding, int maxIm
) {
    vector<std::string> fn;
    /*
        stores the greeting_ascii of
        $ ls | grep *.<fileEnding>
        example:
        $ ls /home/images/testing/9/ | grep *.jpg
        to fn
    **/
    // TODO cv::glob((filePath + string("*") + fileEnding).c_str(), fn, false);
    vector<trainElem> matrices;
    for (int i = 0; i < fn.size() && i < maxIm; i++) {
        trainElem a;
        a.file = fn[i];
        a.label = number;
        matrices.push_back(a);
    }
    fn.erase(fn.begin(), fn.end());
    return matrices;
}

/**
    upload all images in a given directory asssuming the directory contains numLabels sub directories
    *See note above on how the directory is to be organized

    @param basePath the base path for the directory (train in our case)
    @param fileNames the names of the directories inside train
    @param labels the labels for all of the images
    @param numLabels number of directories to test
    @param maxIm the amount of images we want to store (defaults to the amount of images if maxIm greater than the amount)

    @return mainSet a vector  of trainElem (string filename and int label)
*/
trainingSet uploadAllImages(
        const std::string &basePath,
        const char **fileNames,
        int *labels,
        int numLabels,
        const std::string &fileEnding,
        int maxIm
) {
    vector<trainElem> main;
    for (int i = 0; i < numLabels; i++) {

        std::string file = basePath + std::string("/") + fileNames[i] + std::string("/");
        vector<trainElem> b = uploadImages(labels[i], file, fileEnding, maxIm);
        main.insert(main.end(), b.begin(), b.end());
        b.erase(b.begin(), b.end()); //deallocate memory previously in b
    }
    std::shuffle(main.begin(), main.end(), std::mt19937(std::random_device()()));
    trainingSet mainSet;
    mainSet.files = main;
    mainSet.numIn = getNumIn(main[0].file);
    mainSet.numOut = numLabels;
    mainSet.numTestTypes = numLabels;
    mainSet.numPerType = maxIm;
    return mainSet;
}


/**
    gets the number of inputs based on opencv image Matrix

    @param example the item we'll check against
    @return the size of that check item

    @return the size of the input vector
  
    A source of error - mayber images aren't the same size or example is null
*/
int getNumIn(const std::string &example) {
    // TODO
    //Mat A = imread(example, 1);
    // int size = A.rows * A.cols;
    // A.release();
    return 1;
}

/**
    creates a vector based on the desired greeting_ascii (label)

    @param size the size of  the greeting_ascii layer
    @param label the index of the vector to assume 1

    @return a Matrix with 1 in the position we want label to be in
*/
Matrix createOutput(int size, int label) {
    Matrix a(size, 1);
    a.insert(0, 0, 0);
    a.insert(label, 0, 1);
    return a;
}

/**
    Main function trains a set of data with specified network settings

    @param set a trainingSet that we want to train the network with
    @param nHL number of hidden layers
    @param sHL size of hidden Layers
    @param rate the rate of the training process

    @return a Network that has been altered to fit the data
*/
Network *trainDataSet(const trainingSet &set, int nHL, int sHL, float rate) {
    // TODO
    return nullptr;
    /**
    Network *main = new Network(set.numIn, set.numOut, nHL, sHL);
    main->printNetworkSummary();
    for (int i = 0; i < set.files.size(); i++) {
//        printf("%d) Training ..... Label: %d\n", i, set.files[i].label);
        if (i % 100 == 0)printf("%d) training\n", i);
        // Mat A = cv::imread(set.files[i].file, 1); TODO
        if (A.rows != 28 || A.cols != 28) {
            printf("AAAAAA");
            exit(1);
        }
        Matrix B = Matrix(set.numIn, 1);
        //redundant, but I made my own matrix class and imma use it
        for (int j = 0; j < set.numIn; j++)
            B.arr[j] = float(A.data[j] / 255.0);
        A.release();
        Matrix expected = createOutput(set.numOut, set.files[i].label);
        Matrix out = main->propogateNetwork(B);
        main->backPropogateRecurs(out, expected, rate);
    }
    return main;
     */
}

/**
    Just a clean greeting_ascii format to test the network visualy

    @param net the network to train against
    @param mat the matrix to input to the network
    @param expected the expected matrix
*/
bool runOnMatrix(const std::string &filePath, Network *net, int expected) {
    /** TODO
    Mat A = cv::imread(filePath, 1);
    Matrix B(A.rows * A.cols, 1);
    for (int i = 0; i < A.rows * A.cols; i++)
        B.arr[i] = float(A.data[i] / 255.0);
    A.release();
    Matrix out = net->propogateNetwork(B);
    Matrix expect = createOutput(out.dim1, expected);
    return expected == out.getMaxIndex();
     */
    return false;
}


float testOnTestSet(const trainingSet &set, Network *net) {
    int correct = 0;
    int total = 0;
    for (auto &file: set.files) {
        if (runOnMatrix(file.file, net, file.label))correct++;
        total++;
    }
    return float(correct) / float(total);
}
