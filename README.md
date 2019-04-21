# cTensor

### *A Neural Network and Linear Algebra Library in C++*

------

## build instructions
maker is a script that deletes build, makes a cmake project and compiles the project all in one to run. We have not tested this extensively on Windows, so there may be some challenges. There's one line in driver.cpp (src/UI/driver.cpp) that says std::system("-p ...")
this is a unix command that I don't think works on windows, so you can delete this and uncomment the windows version. For the future, we will add compiler flags to test the opperating system. but this wasn't on our agenda.

Going to need more  directions, need to fix CMake and lib folder

Go to build directory
Run the command ```$ make ```
Voila, now you can execute run

## Description

This is a very basic neural network and linear algebra library in C++. 

The program is built using a standard linear algebra approach (does not used optimized BLAS or CUDA libraries, the linear algebra library is done from scratch using un-optimized algorithms) to the classical neural network machine learning technique. 

## Architecture

### Main Data Structure

Our Neural network is build using dynamically allocated layers of Matrices. A Neural Network Layer contains a weights matrix, a bias matrix, a pointer the next layer and a pointer to the previous layer. When we propogate the network, this architecture allows a very quick and efficient means of data storage as we are not storing large arrays of numbers seemingly randomly. Our linear algebra library allows us to store only a single Matrix rather than the indiviudal weights and biases of the network.

Our matrix library is  an area we would like to improve and we are working on improving at the moment. Currently, a matrix is just a single array of dimension (rows * cols). We use a one dimensional array because the jumps between matrix indexes are smaller when each row is directly after the other (where a two dimensional array would require a larger jump in memory - a very small difference, but it adds up when we start building matrices 1000000 - 2000000 elements in size). All the matrix algorithms are standard. We took a standard multiplication method (adding up the standard inner product of the matrix rows and cols).

We are currently working on a sparseMatrix class (you can find it in scratch directory), where only the non zero values of the matrix are stored. Some opperations tend to be more challenging in this approach, such as multiplication and addition, which require the use of permutations of the collumn and row spaces of  the matrices being multiplied. However, all of these are standard in large linear algebra libraries such as openBLAS.

### Linear Algebra Caching Structure

For our user interface, we have a very basic  matrix operations menu. When we store a matrix, we store that matrix in a linked list of MatrixMemories (A matrix and a pointer to the next). To access a matrix, we use very basic operations used commonly on linked lists.

### Future Plans for the Network

If you try this network out, you'll notice the highly unoptimized aspects. It's very slow and not very accurate. This is primarily due to our approach. We chose random functions (sigmoid for our activation function) and we merely used a naive approach of  inputting all of the data into the network at a single  time. Needless to say, there is a great need for optimization and this will continue to be an ongoing project of ours.

<h4 style="font-style:italic;text-align: center;">A C++ library for Machine Learning</h4>
<h3>Summary</h3>
<p>This is not a production level library and should not be treated like one. <br> A machine learning library in c++. 
<h4>Matrix</h4>
<h6 style="font-style:italic">Matrix.cpp -- Matrix.hpp</h6>
A Matrix is a reresentation of a matrix / vector of dimension (m x n). Matrix. Designed primarily for speed, Matrix impliments matrix caching algorithms


<table style="width: 100%;">
	<tr>
		<th>Method</th>
		<th>Description</th>
		<th>Usage</th>
	</tr>
	<tr>
		<td>Matrix()</td>
		<td>Default Constructor</td>
		<td>Creates a 4x4 matrix filled with zero values</td>
	</tr>
	<tr>
		<td>Matrix(int, int)</td>
		<td>Zero Constructor</td>
		<td>Creates a dim1 x dim2 Matrix of zero values</td>
	</tr>
	<tr>
		<td>Matrix(int, int, int)</td>
		<td>Random Number initialized</td>
		<td>Creates a dim1 x dim2 Matrix with random values between zero and desired Max</td>
	</tr>
	<tr>
		<td>add(Matrix)</td>
		<td>Add Method</td>
		<td>Adds {Matrix} to self</td>
	</tr>
	<tr>
		<td>stdMult(Matrix)</td>
		<td>Multiply Method</td>
		<td>Multiplies {Matrix} with self, standard algorithm</td>
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
		<td>returns a Matrix with all values passed through the sigmoid function -- bounds all values between 0 and 1</td>
	</tr>
</table>

<h4>Network</h4>
<h6 style="font-style:italic">network.cpp -- network.hpp</h6>
A network is a linked list data structure for a neural network using Matrices and layer structs.
<h5>struct layer</h5>
A layer struct contains a size, a bias Matrix, a weights Matrix and a pointer to the next layer (nullptr if output layer)

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
		<td>propogateNetwork(Matrix)</td>
		<td>Main opperational method</td>
		<td>Inputs an input vector, feeds input through network by multiplying input by weights, adding biases then applying sigmoid</td>
	</tr>
	<tr>
		<td>printNetwork()</td>
		<td>A print method</td>
		<td>Prints  network in clean format. Prints biases followed by weights matrix</td>
	</tr>
	<tr>
		<td>storeNetwork(string)TODO</td>
		<td>external storage of a network</td>
		<td>stores  network in 'string' filepath as a csv file</td>
	</tr>
	<tr>
		<td>extractNetwork(string)TODO</td>
		<td>extract a csv network</td>
		<td>extracts a network from a csv file</td>
	</tr>
</table>

