#include <iostream>
#include <matLib.hpp>
#include <Network.hpp>
#include <string>

using std::string;

struct MatrixMemory{
    string id;  
    Matrix val;
    MatrixMemory * next;
};


class UI{
    public:
        UI();
        ~UI();
        int Menu();
        bool LinAlgMenu();
        bool operateMenu();
        bool NeuralNetworkMenu();
        bool controlFlow();
        void operationMenu();

        
        void deleteAll();
        void deleteMatrix(string id);
        void printMatrix(string id);
        void printCache();
        void addMatrix(string, string);

        Matrix multiplyMatrices(string, string);        
        Matrix inverse(string);

        Matrix getMatrix(string id);

        Matrix RREF(string);
        Matrix REF(string);
        Matrix add(string, string);
        Matrix principleEigVec(string);
        Matrix transpose(string);
        Matrix sigmoid(string);
        float norm(string);
        
    private:    
        MatrixMemory * head;
        int cacheSize;
};

