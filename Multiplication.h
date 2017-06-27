#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "Multiplier.h"
#include "Configuration.h"

class Multiplication
{
    public:
		virtual Configuration* dispositions (short, short, int*) = 0;
		virtual ~Multiplication () = default;
};

#endif
