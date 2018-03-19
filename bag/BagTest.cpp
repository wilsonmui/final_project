#include <iostream>
#include "Bag.hpp"

int main(){
    Bag<int> intBag;
    std::cout << "pennantVector size: " << intBag.getPennantVectorSize() << std::endl;
    for(int i = 0; i < 10; i ++){
        std::cout << "adding \"" << i << "\" ..." << std::endl;
        intBag.add(i);
        std::cout << "pennantVector size: " << intBag.getPennantVectorSize() << std::endl;
    }
    std::cout << "Test Done." << std::endl;
}