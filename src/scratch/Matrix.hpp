#ifndef MAT_LIB_HPP
#define MAT_LIB_HPP

#include <iostream>
#include <vector>

using std::vector;


namespace matlib{

    //Abstract Class
    template <class T>
    class Matrix{
        public:
            Matrix(){}
            ~Matrix(){}

            int dim1 = 0;
            int dim2 = 0;
            
            virtual void print(){}
            virtual bool insert(int, int, T){return true;};
            virtual T get(int, int);
            virtual T getMax();
            
            //Matrix<T> operator -();
            Matrix<T> operator -();
            Matrix<T> operator =(const float *);

            //binary operrators
            Matrix<T> operator +(Matrix const &);
            Matrix<T> operator -(Matrix const &);
            Matrix<T> operator *(Matrix const &);
            Matrix<T> operator *(float const &);
            Matrix<T> operator +=(Matrix const &);
            Matrix<T> operator -=(Matrix const &);
            Matrix<T> operator *=(Matrix const &);


            //Relational operators
            bool operator <(Matrix const &);
            bool operator >(Matrix const &);
            bool operator ==(Matrix const &);
            bool operator <=(Matrix const &);
            bool operator >=(Matrix const &);

            //type casting
            virtual operator float();

            Matrix<T> operator !(); //inverse (!tensor)
            Matrix<T> operator *(); //transpose (*tensor)
            Matrix<T> operator ~(); //trace (~tensor)

            virtual void replaceRow(int, Matrix);
            virtual void replaceCol(int, Matrix);
            virtual void swapRow(int, int);
            virtual void swapCol(int, int);
            virtual void rref();

        private:
            virtual T normEuclid(){}
            virtual void add(){}
            virtual void minus(){}
            virtual void stdMult(){}
            virtual void scalarMult(){}
            virtual void transpose(){}
            virtual void inverse(){}
            virtual T trace(){}
            



    };
    template <class T>
    class StdMatrix: public Matrix<T>{
        public:
            StdMatrix();
            StdMatrix(int, int);
            StdMatrix(int, int, int);

            void print();
            bool insert(int, int, float);
            T get(int, int);
            T getMax();
        private:
            //Data Structure
            T ** arr;

            T normEuclid();
            void add();
            void minus();
            void stdMult();
            void scalarMult();
            void transpose();
            void inverse();
            T trace();
    };

    template <class T>
    class SparseMatrix: public Matrix<T>{
        public:
            SparseMatrix<T>();
            SparseMatrix<T>(int, int);
            SparseMatrix<T>(int, int, int);
            ~SparseMatrix<T>();
            
            void print();
            bool insert(int, int, T);
            T get(int, int);
            T getMax();
            //Data Structure
            vector<T> elements;
            vector<int> rows;
            vector<int> cols;
        
        private:
    
            T normEuclid();
            void add(SparseMatrix);
            void minus(SparseMatrix);
            void stdMult(SparseMatrix);
            void scalarMult(SparseMatrix);
            void transpose(SparseMatrix);
            void inverse(SparseMatrix);
            //TODO add cases for adding to a regular matrix
            T trace();
    };
}

#endif
