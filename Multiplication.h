#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <vector>
#include "Multiplier.h"
#include "MultiplicationTree.h"

class Multiplication
{
    public:
        virtual vector <MultiplicationTree> dispositions (int, int) = 0;
        virtual ~Multiplication () = default;
};

#endif
