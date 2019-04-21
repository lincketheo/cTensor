#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <matLib.hpp>
#include <vector>

using namespace matlib;
using std::vector;

namespace NetworkLib{
    struct layer{
        int size;
        Matrix inputs;
        Matrix biases;
        Matrix weights;
        layer * next;
        layer * previous;
    };

    class Network{
        public:
            Network(int numIn, int numOut, int numHiddenLayers, int sizeHiddenLayers);
            Network();
            ~Network();
            Matrix propogateOneLayer();
            Matrix propogateNetwork(Matrix inputs);
            void printNetwork();
            void storeNetwork(std::string filename);
            void extractNetwork(std::string filename);
            void printNetworkSummary();
            void backPropogateRecurs(Matrix, Matrix, float);
//            void backPropogate(Matrix, Matrix, float);

        private:
            layer * input;
            layer * output;
            int numberIn;
            int numberOut;
            int layers;
            int layersSize;
    };


    Network trainNetwork(int, int, int, int, int, vector<Matrix>, vector<int>);

}

#endif
