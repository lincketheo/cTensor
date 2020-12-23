#include <iostream>



namespace matlib{

    //Abstract Class
    template <class T>
    class Matrix{
        public:
            virtual Matrix(int, int);
            virtual Matrix(int, int, int);
            virtual Matrix();
            virtual ~Matrix();            

            int dim1;
            int dim2;
            
            virtual void print();
            virtual bool insert(int, int, T);
            virtual T get(int, int);
            virtual T getMax();
            
            Matrix operator -();
            Matrix operator -();
            Matrix operator =(const float *);

            //binary operrators
            Matrix operator +(Tensor const &);
            Matrix operator -(Tensor const &);
            Matrix operator *(Tensor const &);
            Matrix operator *(float const &);
            Matrix operator +=(Tensor const &);
            Matrix operator -=(Tensor const &);
            Matrix operator *=(Tensor const &);


            //Relational operators
            bool operator <(Tensor const &);
            bool operator >(Tensor const &);
            bool operator ==(Tensor const &);
            bool operator <=(Tensor const &);
            bool operator >=(Tensor const &);

            //type casting
            virtual operator float();

            Matrix operator !(); //inverse (!tensor)
            Matrix operator *(); //transpose (*tensor)
            Matrix operator ~(); //trace (~tensor)

            virtual void replaceRow(int, Matrix);
            virtual void replaceCol(int, Matrix);
            virtual void swapRow(int, int);
            virtual void swapCol(int, int);
            virtual void rref();

        private:
            virtual T normEuclid();
            virtual void add();
            virtual void minus();
            virtual void stdMult();
            virtual void scalarMult();
            virtual void transpose();
            virtual void inverse();
            virtual T trace();
            



    }

    template <class T>
    class StdMatrix:public Matrix{
        public:
            Matrix();
            Matrix(int, int);
            Matrix(int, int, int);

            void print();
            bool insert(int, int, float);
            T get(int, int);
            T getMax()
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
    } 

    template <class T>
    class SparseMatrix:public Matrix{
        public:
            Matrix();
            Matrix(int, int);
            Matrix(int, int, int);
            ~Matrix();
            
            void print();
            bool insert(int, int, T);
            T get(int, int);
            T getMax();
        private:
            //Data Structure
            vector<T> elements;
            vector<int> rows;
            vector<int> cols;
    
            T normEuclid();
            void add(SparseMatrix);
            void minus(SparseMatrix);
            void stdMult(SparseMatrix);
            void scalarMult(SparseMatrix);
            void transpose(SparseMatrix);
            void inverse(SparseMatrix);
            //TODO add cases for adding to a regular matrix
            T trace();
    }
}
