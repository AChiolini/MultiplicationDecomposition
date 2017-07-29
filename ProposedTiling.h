#ifndef PROPOSEDTILING_H
#define PROPOSEDTILING_H

#include "Multiplication.h"
#include "Multiplier.h"
#include "MultiplicationTree.h"

class ProposedTiling : public Multiplication
{
    private:
        Multiplier *multipliers;
        int nMultipliers;
        MultiplicationTree dispose(short, short, int);

    public: 
        ProposedTiling(Multiplier*, int);
        MultiplicationTree* dispositions(short, short, int*);
        virtual ~ProposedTiling() = default;
};

#endif
