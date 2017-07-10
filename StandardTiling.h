#ifndef STANDARDTILING_H
#define STANDARDTILING_H

#include "Multiplication.h"
#include "Multiplier.h"
#include "MultiplicationTree.h"

class StandardTiling : public Multiplication
{
    private:
        Multiplier *multipliers;
		int nMultipliers;
        MultiplicationTree dispose(short, short, int);

    public: 
        StandardTiling(Multiplier*, int);
        MultiplicationTree* dispositions(short, short, int*);
        ~StandardTiling() = default;
};

#endif