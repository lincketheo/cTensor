#ifndef MATLIB_HPP
#define MATLIB_HPP

#include <iostream>
#include <vector>

using std::vector;


    template <class T>
    class Matrix{
        public:
            int dim1 = 0;
            int dim2 = 0;

            virtual void print();


    };


    template <class T>
    class Matrix2: public Matrix<T> {
        public:
            Matrix2(int, int);

            void print();

    };


#endif
