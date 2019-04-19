#include <userInterFace.hpp>
#include <iostream>
#include <matLib.hpp>


int main(){
    UI main;
    
    main.addMatrix("[1 2 3; 4 5 6; 7 8 9]", "A");
    main.printCache();
    main.addMatrix("[2 4 5; 9 0 1; 9 9 1]", "B");
    main.printCache();

    return 0;
}
