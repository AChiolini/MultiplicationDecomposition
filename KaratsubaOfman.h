#ifndef KARATSUBAOFMAN_H
#define KARATSUBAOFMAN_H

#include "Multiplication.h"
#include "Multiplier.h"

class KaratsubaOfman : public Multiplication
{
    private:
        Multiplier *multipliers;
		int nMultipliers;
        Configuration dispose(short, short, int);

    public: 
        KaratsubaOfman(Multiplier*, int);
        Configuration* dispositions(short, short, int*);
        ~KaratsubaOfman() = default;
};

#endif