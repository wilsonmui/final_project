#include "Bag.hpp"
#include "Pennant.hpp"
#include <vector>

template <typename T>
Bag<T>::Bag(){
}

template <typename T>
void Bag<T>::add(T element){
    Pennant<T>* newPennant = new Pennant<T>(element);
    for(int i = 0; i < pennantVector.size; i++){
        if(pennantVector[i] == NULL){
            pennantVector[i] = newPennant;
            return;
        }else{
            newPennant = merge(newPennant, pennantVector[i]);
            pennantVector[i] = NULL;
        }
    }
    pennantVector.push_back(newPennant);
}
