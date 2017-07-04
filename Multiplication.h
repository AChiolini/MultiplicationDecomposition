#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "Multiplier.h"
#include "MultiplicationTree.h"

class Multiplication
{
    public:
		virtual MultiplicationTree* dispositions (short, short, int*) = 0;
		virtual ~Multiplication () = default;
};

#endif
