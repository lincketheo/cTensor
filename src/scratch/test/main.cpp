#include "main.hpp"


using namespace std;


template <class T>
void Matrix<T>::print(){
    cout<<"hi there"<<endl;
}

template <class T>
Matrix2<T>::Matrix2(int i, int j){
    cout<<i<<" "<<j<<endl;
}

template <class T>
void Matrix2<T>::print(){
    cout<<"yo"<<endl;
}

int main(){
    Matrix<int> * a;
    
    Matrix2<int> a2(3, 3);
    
    a = &a2;
    
    a->print();
    return 0;

}
