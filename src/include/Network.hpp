#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <matLib.hpp>

using namespace matlib;
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
}

#endif
