#include <stdio.h>


struct Node {
    int value;
    Node* left_;
    Node* right_;
};

class Pennant{
    
    Node* root;
    int size;
    
    Pennant();
    Pennant(Node* n);
    void union(Pennant* pennant);
    Pennant* split(Pennant* Pennant);
    ~Pennant();
    
}
