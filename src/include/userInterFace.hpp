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

        
        void deleteAll();
        void deleteMatrix(string id);
        void printMatrix(string id);
        void printCache();
        void addMatrix(string, string);
        
        Matrix getMatrix(string id);
        
    private:    
        MatrixMemory * head;
        int cacheSize;
};

