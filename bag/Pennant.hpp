#pragma once

#include <cstddef>

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
    static Pennant merge(Pennant<T>*& a, Pennant<T>*& b);
    //Pennant split();
};
