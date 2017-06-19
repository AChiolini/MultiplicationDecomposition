#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "Multiplier.h"
#include "SubMultiplication.h"

class Multiplication
{
    private:
	Multiplier *multipliers;
	int nMultipliers;
	void printMatrix (char*, short, short);
	SubMultiplication* standardDisposition (Multiplier*, short, short);

    public:
	Multiplication ();
	void printMultipliers();
	long long multiply(short, long long, short, long long);
	virtual ~Multiplication () = default;
};

#endif
