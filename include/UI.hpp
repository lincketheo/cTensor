#include <iostream>
#include <Matrix.hpp>
#include <Network.hpp>
#include <string>

using std::string;

struct MatrixMemory {
    string id;
    Matrix val;
    MatrixMemory *next;
};


class UI {
public:
    UI();

    ~UI();

    static int mainDisplay();

    static int Menu();

    bool LinAlgMenu();

    bool operateMenu();

    int neuralNetworkMenu();

    bool controlFlow(const char **, int *);

    void operationMenu();

    void deleteAll();

    void deleteMatrix(const string &id);

    void printMatrix(string id);

    void printCache();

    void addMatrix(const string &, const string &);

    Matrix multiplyMatrices(const string &, const string &);

    Matrix inverse(const string &);

    Matrix getMatrix(const string &id);

    Matrix RREF(const string &);

    Matrix REF(const string &);

    Matrix add(const string &, const string &);

    Matrix principleEigVec(const string &);

    Matrix transpose(const string &);

    Matrix sigmoid(const string &);

    float norm(const string &);

    void propogateNeuralNetwork(const char **, int *);

private:
    MatrixMemory *head;
    int cacheSize;
    int numLabels = 10;
    std::string trainingFileBase;
    std::string testingFileBase;
    std::string fileEnding;
    int nHL{};
    int sHL{};
    float rate{};
    int numReps{};
    Network *main;
};

