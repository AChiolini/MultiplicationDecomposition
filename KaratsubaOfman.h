#ifndef KARATSUBAOFMAN_H
#define KARATSUBAOFMAN_H

#include "Multiplication.h"
#include "Multiplier.h"

class KaratsubaOfman : public Multiplication
{
    private:
        Multiplier *multipliers;
		int nMultipliers;
        MultiplicationTree dispose(short, short, int);

    public: 
        KaratsubaOfman(Multiplier*, int);
        MultiplicationTree* dispositions(short, short, int*);
        ~KaratsubaOfman() = default;
};

#endif