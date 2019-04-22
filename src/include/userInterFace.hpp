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
        int mainDisplay();
        int Menu();
        bool LinAlgMenu();
        bool operateMenu();
        int neuralNetworkMenu();
        bool controlFlow(const char **, int *);
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
        void propogateNeuralNetwork(const char **, int *);        

    private:    
        MatrixMemory * head;
        int cacheSize;
        int numLabels = 10;
        std::string trainingFileBase;
        std::string testingFileBase;
        std::string fileEnding;
        int nHL;
        int sHL;
        float rate;
        int numReps;
        NetworkLib::Network * main;
};

