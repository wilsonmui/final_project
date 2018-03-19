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
    void union(Bag bag);
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

Bag* Bag::split(){
    Bag bag = new Bag();
    Pennant<T> y = pennantVector[0];
    pennantVector[0] = NULL;
    for(int k = 1; k < pennantVector.size(); k++){
        if(pennantVector[k] != NULL){
            bag->pennantVector[k-1] = pennantVector[k].split;
            pennantVector[k-1] = pennantVector[k];
            pennantVector[k] = NULL;
        }
    }
    
    if (y != NULL){
        insert(y);
    }
    
    return bag;
}

void Bag::union(Bag bag){
    Pennant<T> y = new Pennant<T>();
    for (int k = 0; k < pennantVector.size(); k++){
        FA(pennantVector[k], bag->pennantVector[k], y);
    }
}

//helper function for union. Full-adder function
void FA(Pennant<T> *x, Pennant<T> *y, Pennant<T> *z) {
    
    if(z == NULL && y!= NULL && x != NULL) {
        x->merge(y);
        z = x;
        x = NULL;
    }
    else if(y == NULL && x != NULL && z != NULL) {
        x->merge(z);
        z = x;
        x = NULL;
    }
    else if(x == NULL && y != NULL && z != NULL) {
        y->merge(z);
        z = y;
        x = NULL;
    }
    else if (x != NULL && y != NULL && z != NULL){
        y->merge(z);
        z = y;
    }
}
