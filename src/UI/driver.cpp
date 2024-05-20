/**
    CS-11 Asn 2, driver.cpp
    Purpose: provide user interaction content for the neural network

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/
#include <userInterFace.hpp>        //main header file
#include <iostream>                 //printf std
#include <matLib.hpp>               //used for matrix caching
#include <string>                   //to filter user inputs
#include <Network.hpp>              //to train the neural network
#include <networkTrain.hpp>         //obtain datasets from folders
#include <constants.hpp>            //fileBaseCONSTANT fileBaseTestCONSTANT
#include <limits>                   //flush

using std::string;
using namespace NetworkLib;
using namespace matlib;
using namespace training;


//null construction of UI
UI::UI(){
    main = nullptr;
    head = nullptr;
    cacheSize = 0;
}

//deletes matrix cache
UI::~UI(){
    deleteAll();
}

//First menu greeting
int UI::Menu(){
    int option;
    printf("============ cTensor Main Menu ============\n");
    printf("Enter a main option below:\n");
    printf("1) Linear Algebra\n");
    printf("2) Neural Networks\n");
    printf("3) Quit\n");
    std::cin>>option;
    std::cout<<option<<std::endl;
    if(option < 1 || option > 3)return -1;
    return option;
}

//matrix operator menu
void UI::operationMenu(){
    printf("============ cTensor Linear Algebra Operation Menu ============\n");
    printf("1) Multiply two matrices\n");
    printf("2) Add two matrices\n");
    printf("3) Get the inverse of a matrix\n");
    printf("4) Get the norm of a matrix\n");
    printf("5) Get the principal eigenvector\n");
    printf("6) RREF A matrix\n");
    printf("7) REF A matrix\n");
    printf("8) Get the transpose of a Matrix\n");
    printf("9) Get the sigmoid function of a matrix\n");
    int option;
    std::cin>>option;
    switch(option){
        case(1):{
            string id1, id2;
            printf("Matrix 1 = \n");
            std::cin.ignore();
            std::getline(std::cin, id1);
            std::cout<<id1<<std::endl;
            printf("Matrix 2 = \n");
            std::getline(std::cin, id2);
            multiplyMatrices(id1, id2);
            return; 
        }
        case(2):{
            string id1, id2;
            printf("Matrix 1 = \n");
            std::cin.ignore();
            std::getline(std::cin, id1);
            printf("Matrix 2 = \n");
            std::getline(std::cin, id2);
            add(id1, id2);
            return;
        }
        case(3):{
            string id;
            printf("Matrix = \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            inverse(id);
            return;
        }
        case(4):{
            string id;
            printf("Matrix = \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            norm(id);
            return;
        }
        case(5):{
            string id;
            printf("Matrix = \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            principleEigVec(id);
            return;
        }
        case(6):{
            string id;
            printf("Matrix = \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            RREF(id);
            return;
        }
        case(7):{
            string id;
            printf("Matrix = \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            REF(id);
            return;
        }
        case(8):{
            string id;
            printf("Matrix = \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            transpose(id);
            return;
        }
        case(9):{
            string id;
            printf("Matrix = \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            sigmoid(id);
            return;
        }
        case(10):{
            return;
        }
        default: return;

            
    }
    //printf("6) Quit\n");
}

//main linear algebra menu
bool UI::LinAlgMenu(){
    string inputS;
    printf("============ cTensor Linear Algebra Menu ============\n");
    printf("1) Create a Matrix\n");
    printf("2) Operate on a matrix\n");
    printf("3) Get Matrix cache\n");
    printf("4) Delete Matrix\n");
    printf("5) Delete All Matrices\n");
    printf("6) Quit\n");
    std::cin >> inputS;
    int input = std::stoi(inputS);
    switch(input){
        case 1: {
            string id;
            string inMat;
            printf("Enter Matrix Variable: \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            printf("Enter Matrix: \n");
            printf("In the form of: a b c;d e f;g h i\n");
            printf("Ex:   1.2 3.4 5.6;9.0 9 1;1 0 2.1;4.113 8.102 9.0\n");
            std::getline(std::cin, inMat);
            std::cout<<inMat;
            addMatrix(inMat, id);
            printf("\n");
            return true;
            }
        case 2:
            operationMenu();
            return true;
        case 3:
            printCache();
            return true;
        case 4:{
            string id;
            printf("Enter the Matrix to Delete: \n");
            std::cin.ignore();
            std::getline(std::cin, id);
            deleteMatrix(id);
            return true;
            }
        case 5:
            deleteAll();
            return true;
        case 6:
            printf("Goodbye!\n");
            return false;
        default:
            printf("Please enter a valid option\n");
            return true;
    }
    return false;
}

//Neural Network menu
int UI::neuralNetworkMenu(){
    int inputS;
    printf("============ Neural Network Main Menu ============\n");
    printf("1) Begin\n");
    printf("2) Quit\n");
    std::cin >> inputS;
    switch(inputS){
        case 1:
        {
            printf("Welcome! We'll get things set right up for you in a second, \n");
            printf("Please note that if a file path is incorrect, unexpected results may occur (Done my best to conteract this, but stuff happens\n");
            printf("First, Enter training directory (no need to end in a /): \n>> ");
            std::cin.ignore();
            getline(std::cin, trainingFileBase);
            if(trainingFileBase.empty()){
//                trainingFileBase = "/home/theo/Documents/projects/math/neuralNets/cTensor/src/Data/images/mnist_jpgfiles/train";
                    trainingFileBase = fileBaseCONSTANT;
            }
            printf("Using Training Directory: \n>> %s\n\n", trainingFileBase.c_str());
            printf("Please Enter testing directory (no need to end in a /): \n>> ");
            getline(std::cin, testingFileBase);
            if(testingFileBase.empty()){
//                testingFileBase = "/home/theo/Documents/projects/math/neuralNets/cTensor/src/Data/images/mnist_jpgfiles/test";

                testingFileBase = fileBaseTestCONSTANT;
            }

            printf("Using Testing Directory: \n>> %s\n\n", testingFileBase.c_str());
            printf("Please enter the file ending (jpg, jpeg, png etc.)\n>> ");
            getline(std::cin, fileEnding);
            if(fileEnding.empty()){
                fileEnding = fileEndingCONSTANT; 
            }
            printf("Using fileEnding: \n>> %s\n\n", fileEnding.c_str());
            printf("=========== Now we'll set up the network ============\n");
            printf("For reference:\nLayers = 1 Rate = 0.008 nodes = 600\nAccuracy = 0.4839\n");
            printf("Layers = 2 Rate = 0.009 nodes = 320\nAccuracy = 0.9123 (takes 12 hours)\n");
            printf("Short (under 10 minutes) training sessions typically get around 0.3 - 0.4\n");
            printf("Longer training sessions on looping recursive image batch produces max 0.91\n");
            printf("Enter Desired Number of Hidden Layers\n");
            scanf("%d", &nHL);
            printf("Enter size of the hidden Layers\n");
            scanf("%d", &sHL);
            printf("Enter the training rate\n");
            scanf("%f", &rate);
            printf("Enter the number of repetitions per image to train with\n");
            scanf("%d", &numReps);
            printf("Using: \n%d Hidden Layers\n%d nodes per hidden layer\n%d images per label\n%f training rate\n", nHL, sHL, numReps, rate);
            return 1;
        }   
        case 2:
            return 0;
        default:
            printf("invalid");
            return -1;
            
    }
    return 0;
}

//main propogation 
void UI::propogateNeuralNetwork(const char ** fileNames, int * labels){
    
    trainingSet testing = uploadAllImages(trainingFileBase, fileNames, labels, numLabels, fileEnding, numReps);
    for(int i = 0; i < testing.files.size(); i++){
            std::cout<<testing.files[i].file<<std::endl;
    }
    main = trainDataSet(testing, nHL, sHL, rate);
}

//main display
int UI::mainDisplay(){
    int inputs;
    printf(" _________\n< cTensor >\n ---------\n        \\   ^__^\n         \\  (oo)\\_______\n            (__)\\       )\\/\\\n                ||----w |\n                ||     ||\n");




    //printf("       ooooo                                  \n         8                                    \n.oPYo.   8   .oPYo. odYo. .oPYo. .oPYo. oPYo.\n8    '   8   8oooo8 8' `8 Yb..   8    8 8  `' \n8    .   8   8.     8   8   'Yb. 8    8 8     \n`YooP'   8   `Yooo' 8   8 `YooP' `YooP' 8     \n:.....:::..:::.....:..::..:.....::.....:..::::\n::::::::::::::::::::::::::::::::::::::::::::::\n:::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\nA pretty ok nerual network and Linear Algebra Library in C++\n");
    std::cout<<"Press ENTER to continue ....."<< std::flush;
    std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n' );
    //std::system("read -p 'Press Enter to continue...' var"); //for linux
    //std::system("pause"); //for windows
    printf("\n");
    return -1;
}

//main driver control flow
bool UI::controlFlow(const char ** fileNames, int* labels){
    mainDisplay();
    int i = 0;
    i = Menu();
    while(i == -1){
        i = Menu();
    }
    std::cout<<std::endl;
    if(i == 1){
        while(LinAlgMenu()){};
        return false;
    }
    else if(i == 2){
        i = neuralNetworkMenu();
        while(i == -1){
            i = neuralNetworkMenu();
        }
        if(i == 0){
            printf("Goodbye!\n");
            return true;
        }
        
        propogateNeuralNetwork(fileNames, labels);
        trainingSet testing2 = uploadAllImages(testingFileBase, fileNames, labels, numLabels, "jpg", 100);
        for(int i = 0; i < testing2.files.size(); i++){
            std::cout<<testing2.files[i].file<<std::endl;
        }
        main->printNetwork();
        main->printNetworkSummary();
        float result = testOnTestSet(testing2, main);   
        std::cout<<result<<std::endl;
 
        return true;
    }
    else if(i == 3){
        printf("Goodbye!\n");
        return true;
    }
    printf("oops something went wrong\n");
    return false;
}

void UI::deleteAll(){
    while(head != nullptr){
        MatrixMemory * temp = head;
        head = head->next;
        delete temp;
    }
}

//delete a specific matrix in cache
void UI::deleteMatrix(string id){
    MatrixMemory * temp = head;
    while(temp->next != nullptr){
        if(temp->next->id == id){
            printf("deleting %s \n", id.c_str());
            MatrixMemory * temp2 = temp->next;
            temp->next = temp2->next;
            delete temp2;     
            return;
        }
        temp = temp->next;
    }
}

//print a specific matrix in cache
void UI::printMatrix(string id){
    getMatrix(id).print();  
}

//print the entire cache
void UI::printCache(){
    MatrixMemory * temp = head;
    while(temp != nullptr){
        printf("%s = \n", temp->id.c_str());
        temp->val.print();
        temp = temp->next;
    }
}

//========================================= Operators ================================
void UI::addMatrix(string matrixIn, string id){
    if(head == nullptr){
        MatrixMemory * value = new MatrixMemory;
        value->val = Matrix(matrixIn);
        value->id = id;
        value->next = nullptr;
        head = value;
        return;
    }
    MatrixMemory * temp = head;
    while(temp->next != nullptr)temp = temp->next;
    MatrixMemory * newMemory = new MatrixMemory;
    newMemory->val = Matrix(matrixIn);
    newMemory->id = id;
    newMemory->next = nullptr;
    temp->next = newMemory;
}

Matrix UI::getMatrix(string id){
    MatrixMemory * m = head;
    while(m != nullptr){
        if(m->id == id)return m->val;
        m = m->next;
    }
    printf("Couldn't Find matrix %s\n", id.c_str());
    printf("Default Matrix is Identiy \n");
    Matrix a;
    return a;
}

Matrix UI::multiplyMatrices(string id1, string id2){
    Matrix p = getMatrix(id1) * getMatrix(id2);
    p.print();
    return p;
}

Matrix UI::inverse(string id){
    Matrix p = !getMatrix(id);
    p.print();
    return p;
}

Matrix UI::RREF(string id){
    getMatrix(id).GaussJordanRREF();
    Matrix p = getMatrix(id);
    p.print();  
    return p;
}

Matrix UI::REF(string id){
    getMatrix(id).GaussJordan();
    Matrix p = getMatrix(id);
    p.print();
    return p;
}

Matrix UI::add(string id1, string id2){
    Matrix p = getMatrix(id1) + getMatrix(id2);
    p.print();
    return p;
}

Matrix UI::principleEigVec(string id){
    Matrix p = getMatrix(id).principalEig(100);
    p.print();
    return p;
}

Matrix UI::transpose(string id){
    Matrix p = *getMatrix(id);
    p.print();
    return p;
}
   
Matrix UI::sigmoid(string id){
    getMatrix(id).sigmoid().print();
    Matrix p = getMatrix(id);
    return p;
} 

float UI::norm(string id){
    float i = float(getMatrix(id));
    std::cout<<std::endl;
    std::cout<<i<<std::endl;
    return i;
}
