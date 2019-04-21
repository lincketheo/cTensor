#include <userInterFace.hpp>
#include <iostream>
#include <matLib.hpp>
#include <string>

using std::string;

UI::UI(){
    head = nullptr;
    cacheSize = 0;
}

UI::~UI(){
    deleteAll();
}

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
            //std::cin.ignore();
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
            //std::cin.ignore();
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


    printf("6) Quit\n");


}

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
        case 5:
            deleteAll();
            return true;
        case 6:
            printf("Goodbye!");
            return false;
        default:
            printf("Please enter a valid option\n");
            return true;
    }
    return false;
}

bool UI::controlFlow(){
    if((Menu()) != 1)exit(1);
    bool status = true;
    while(status){
        status = LinAlgMenu();
    }
    printf("oops you dun\n");
    return false;
}

void UI::deleteAll(){
    while(head != nullptr){
        MatrixMemory * temp = head;
        head = head->next;
        delete temp;
    }
}

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

void UI::printMatrix(string id){
    getMatrix(id).print();  
}

void UI::printCache(){
    MatrixMemory * temp = head;
    while(temp != nullptr){
        printf("%s = \n", temp->id.c_str());
        temp->val.print();
        temp = temp->next;
    }
}

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
