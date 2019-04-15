/**
    CS-11 Asn 2, MatLib.cpp
    Purpose: Second level matrix opperators

    @author Theo Lincke, Kyle Zhou
    @version 1.1 4/17/19
*/

#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Matrix.hpp"


using namespace matlib;
using namespace kernel;

/*
    Return

    @param
    @return
*/
Matrix mat_add(Matrix, Matrix);
/*
    Return

    @param
    @return
*/
Matrix mat_mul(Matrix, Matrix);
/*
    Return

    @param
    @return
*/
Matrix inverse(Matrix);
/*
    Return

    @param
    @return
*/
Matrix transpose(Matrix);
/*
    Return

    @param
    @return
*/
Matrix rref(Matrix); //rref will just rref it, should be augmented already
/*
    Return

    @param
    @return
*/
Matrix solveSystem(Matrix, Matrix);
/*
Matrix lu(Matrix, Matrix);
Matrix eigen(Matrix);
Matrix eigenVec(Matrix);
Matrix svd(Matrix);
//and more to come
*/
