#include "Pennant.h"

class Bag{
    
    Pennant **point;
    
    Bag();
    Bag(int n);
    void add(Pennant* pennant);
    Bag* divide();
    ~Bag();
    
}
