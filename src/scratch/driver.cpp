#include <iostream>


struct MatrixMemory{
    std::string id;
    Matrix val;
    MatrixMemory * next; 
}

struct Session{
    MatrixMemory * head;
    int numMatrices;
}

void deleteMatrixMemory(MatrixMemory * m){
    while(m != nullptr){
        MatrixMemory * temp = m;
        m = m->next;
        delete temp;
    }  
}

void deleteMatrixFromMemory(MatrixMemory * m, std::string id){
    while(m != nullptr){
        if(m->id == id){
            MatrixMemory * temp = m;
            m = m->next;
            delete temp;
        }
        m = m->next;
    }
}

void printMatrixMemory(MatrixMemory * m){
    while(m != nullptr){
        printf("%s = \n", m->id.c_str());
        m->val.print();
        printf("\n");
    }
}

void printMatrix(MatrixMemory * m, std::string id){
    search(m, id).print();
}


Matrix search(MatrixMemory * m, std::string id){
    while(m != nullptr){
        if(m->id == id)return m->val;
        m = m->next;
    }
    printf("Couldn't find matrix %s\n", id.c_str());  
    printf("Default Matrix is Identity \n");
    Matrix a();
    return a;
}
    
int Menu(){
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

int LinAlgMenu(Session &main){
    std::string input;
    printf("============ cTensor Linear Algebra Menu ============\n");
    printf("1) Create a Matrix\n");
    printf("2) Operate on a matrix\n");
    printf("3) Get Matrix cache\n");
    printf("4) Delete Matrix\n");
    printf("5) Delete All Matrices\n");
    cin >> input;
    switch(input){
        case 1:
            addMatrix(main.head, input);
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
}




int main(){
    int a = Menu();

    std::cout<<a<<std::endl;
    return 0;

}
