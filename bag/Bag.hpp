#pragma once

#include "Pennant.hpp"
#include <vector>

template <typename T>
class Bag{
private:
    std::vector<Pennant<T> *> pennantVector;
    
public:
    Bag(){};
    void add(T element);
    Bag* split();
    int getPennantVectorSize(){return pennantVector.size();}
};

template <typename T>
void Bag<T>::add(T element){
    Pennant<T>* newPennant = new Pennant<T>(element);
    for(int i = 0; i < pennantVector.size(); i++){
        if(pennantVector[i] == NULL){
            pennantVector[i] = newPennant;
            return;
        }else{
            newPennant = Pennant<T>::merge(newPennant, pennantVector[i]);
            pennantVector[i] = NULL;
        }
    }
    pennantVector.push_back(newPennant);
}
