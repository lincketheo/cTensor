# cTensor
## build instructions
This was built on a linux  environment and I am not sure the best way to build using windows or if you can, butassuming you are using a unix environment, all you need to do is run the maker command (removes build rebuilds  the project moving two executables to bin folder

You'll need OpenCV Installed - I just used it to read images. I think I'll bake up my own asap so that I don't 
have to depend on such a big library. 

```bash
    $ mkdir build
    $ cd build
    $ cmake ..
```


## Description

<h4 style="font-style:italic;text-align: center;">A C++ library for Machine Learning</h4>
<h3>Summary</h3>
<p>This is not a production level library and should not be treated like one. <br> A machine learning library in c++. 
<h4>Tensor</h4>
<h6 style="font-style:italic">tensor.cpp -- tensor.hpp</h6>
A Tensor is a reresentation of a matrix / vector of dimension (m x n). Tensor. Designed primarily for speed, tensor impliments matrix caching algorithms

<table style="width: 100%;">
	<tr>
		<th>Method</th>
		<th>Description</th>
		<th>Usage</th>
	</tr>
	<tr>
		<td>Tensor()</td>
		<td>Default Constructor</td>
		<td>Creates a 4x4 matrix filled with zero values</td>
	</tr>
	<tr>
		<td>Tensor(int, int)</td>
		<td>Zero Constructor</td>
		<td>Creates a dim1 x dim2 Matrix of zero values</td>
	</tr>
	<tr>
		<td>Tensor(int, int, int)</td>
		<td>Random Number initialized</td>
		<td>Creates a dim1 x dim2 Matrix with random values between zero and desired Max</td>
	</tr>
	<tr>
		<td>add(Tensor)</td>
		<td>Add Method</td>
		<td>Adds {Tensor} to self</td>
	</tr>
	<tr>
		<td>stdMult(Tensor)</td>
		<td>Multiply Method</td>
		<td>Multiplies {tensor} with self, standard algorithm</td>
	</tr>
	<tr>
		<td>transpose()</td>
		<td>transpose method</td>
		<td>returns transpose of self</td>
	</tr>
	<tr>
		<td>getShape()</td>
		<td>returns dimensions</td>
		<td>returns a sized 2 array with index 0, 1 as dim1 dim2</td>
	</tr>
	<tr>
		<td>sigmoid()</td>
		<td>sigmoid opperation</td>
		<td>returns a tensor with all values passed through the sigmoid function -- bounds all values between 0 and 1</td>
	</tr>
</table>

<h4>Network</h4>
<h6 style="font-style:italic">network.cpp -- network.hpp</h6>
A network is a linked list data structure for a neural network using Tensors and layer structs.
<h5>struct layer</h5>
A layer struct contains a size, a bias Tensor, a weights tensor and a pointer to the next layer (nullptr if output layer)

<table style="width: 100%;">
	<tr>
		<th>Method</th>
		<th>Description</th>
		<th>Usage</th>
	</tr>
	<tr>
		<td>Network(int, int, int, int)</td>
		<td>Default Constructor</td>
		<td>Initializes a network with numHidden layers hidden layers of size size hiddenlayers. All layers have biases and weights initialized to random matrces / vectors</td>
	</tr>
	<tr>
		<td>propogateNetwork(Tensor)</td>
		<td>Main opperational method</td>
		<td>Inputs an input vector, feeds input through network by multiplying input by weights, adding biases then applying sigmoid</td>
	</tr>
	<tr>
		<td>printNetwork()</td>
		<td>A print method</td>
		<td>Prints  network in clean format. Prints biases followed by weights matrix</td>
	</tr>
	<tr>
		<td>storeNetwork(string)</td>
		<td>external storage of a network</td>
		<td>stores  network in 'string' filepath as a csv file</td>
	</tr>
	<tr>
		<td>extractNetwork(string)</td>
		<td>extract a csv network</td>
		<td>extracts a network from a csv file</td>
	</tr>
</table>
