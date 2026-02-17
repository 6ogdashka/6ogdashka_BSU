#include <iostream>
#include "TempleteClass.h"

int main() {

    DynamicArrayFactory Fabric;
    
    std::vector<int> OldVec = {1,2,3,4,5,6,7,8,9,10};
    DynamicArray mama(Fabric.createArray<int>(OldVec));

    std::vector<double> OldVec1 = {0.0,0.2,0.3,0.4,0.5,0.6,0.6,0.7,0.8,0.9};
    DynamicArray papa(Fabric.createArray<double>(OldVec1));

    std::vector<char> OldVec2 = {'a','b','c','d','e','f','g','h','i','j'};
    DynamicArray gitler = (Fabric.createArray<char>(OldVec2));

    std::cout << mama.size() << "\n" << mama[5] << "\n";
    std::cout << papa.size() << "\n" << papa[5] << "\n";
    std::cout << gitler.size() << "\n" << gitler[5] << "\n";

}