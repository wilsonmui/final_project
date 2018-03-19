#pragma once

#include "Pennant.hpp"
#include <vector>

template <typename T>
class Bag{
    std::vector<Pennant<T> *> pennantVector;
    
    Bag();
    void add(T element);
    Bag* split();
};
