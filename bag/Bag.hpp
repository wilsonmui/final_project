#include "Pennant.h"

class Bag{
    int size;
    Pennant **point;
    
    Bag();
    Bag(int n);
    void add(Pennant* pennant);
    union(Bag bag);
    Bag* split();
    Bag* divide();
    ~Bag();
    
}
