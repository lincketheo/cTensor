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

bool UI::LinAlgMenu(){
    string inputS;
    printf("============ cTensor Linear Algebra Menu ============\n");
    printf("1) Create a Matrix\n");
    printf("2) Operate on a matrix\n");
    printf("3) Get Matrix cache\n");
    printf("4) Delete Matrix\n");
    printf("5) Delete All Matrices\n");
    std::cin >> inputS;
    int input = std::stoi(inputS);
    /*
    switch(input){
        case 1:
            addMatrix(input);
            return true;
        case 3:
            printMatrixMemory(main.head);
            return true;
        case 5:
            deleteMatrixMemory(main.head);
            return true;
        case 6:
            printf("Goodbye!");
            return false;
        default:
            printf("Please enter a valid option\n");
            return true;
    }
    return false;
    */
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


