#include "Pennant.hpp"

template <typename T>
static Pennant Pennant<T>::merge(Pennant<T>*& a, Pennant<T>*& b){
    if(a-> treeHeight != b-> treeHeight){
        throw std::invalid_argument("cannot merge two pennant of different height");
    }
    
    Pennant<T> newPennant(b.extraElement);
    newPennant.rootNode = Node();
    newPennant.rootNode.element = a.extraElement;
    newPennant.rootNode.left = a.rootNode;
    a.rootNode = NULL;
    newPennant.rootNode.right = b.rootNode;
    b.rootNode = NULL;

    delete a;
    delete b;
    a = NULL;
    b = NULL;

    return newPennant;
}

template <typename T>
Pennant<T>::~Pennant(){
    if(rootNode != NULL){
        delete rootNode;
    }
}