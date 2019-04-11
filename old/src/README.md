# A Neural Network Library in low level c and assembly

This is ** not ** a production level machine learning library. This is a side project so do not use this in production.

## Description:
At the initial points, all there is is a Tensor class with naive approaches at optimization. You'll notice the tensor matmul method just calls stdmult which is standard mult. This is because in the future, matrix multiplication will be optimized. 

## A network:
A network consists of m layers, an input layer, an output layer and m - 2 inner layers. Each layer (except for the output layer) is a struct that consists of three tensors, an input and biase tensor (n x 1 vectors), a weights tensor (o x i where o is the number of outputs and i is the number of inputs) and a next layer. each layer will feed it's output to next tensor (this is a linked list implimentation) via calculate Output as the input to next layer pointer.
A Network is defined by its head, it propogates layers and a print network is used for convinience. storenetwork and extract network creates an easy approach at storing networks in external (most likely csv file). input is the head, numin and numout are defined as the number of inputs and number of outputs. Layers is the number of layers including in and out.

## k means

