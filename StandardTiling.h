#ifndef STANDARDTILING_H
#define STANDARDTILING_H

#include "Multiplication.h"
#include "Multiplier.h"

class StandardTiling : public Multiplication
{
    private:
        Configuration dispose(short, short, int);

    public: 
        StandardTiling(Multiplier*, int);
        Configuration* dispositions(short, short, int*);
        ~StandardTiling() = default;
};

#endif