#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class Pennant{
private:
    struct Node{
        Node* left;
        Node* right;
        T element;
    };
    Node* rootNode;
    T extraElement;
    unsigned treeHeight;
    
public:
    Pennant(int element) : rootNode(NULL), treeHeight(0), extraElement(element) {};
    static Pennant* merge(Pennant<T>*& a, Pennant<T>*& b);
    //Pennant split();
    ~Pennant();
    vector<int> dumpVertices();
};

template <typename T>
Pennant<T>* Pennant<T>::merge(Pennant<T>*& a, Pennant<T>*& b){
    if(a-> treeHeight != b-> treeHeight){
        throw std::invalid_argument("cannot merge two pennant of different height");
    }
    
    Pennant<T>* newPennant = new Pennant<T>(b->extraElement);
    newPennant->rootNode = new Node();
    newPennant->rootNode->element = a->extraElement;
    newPennant->rootNode->left = a->rootNode;
    a->rootNode = NULL;
    newPennant->rootNode->right = b->rootNode;
    b->rootNode = NULL;
    newPennant->treeHeight = a->treeHeight+1;

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
