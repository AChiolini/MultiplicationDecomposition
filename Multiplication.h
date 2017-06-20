#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "Multiplier.h"
#include "Configuration.h"

class Multiplication
{
    private:
	Multiplier *multipliers;
	int nMultipliers;
	void printMatrix (char*, short, short);
	Configuration* standardDisposition (Multiplier*, short, short);
	void KaratsubaOfman (long long, long long, short, short);

    public:
	Multiplication ();
	void printMultipliers();
	long long multiply(short, long long, short, long long);
	virtual ~Multiplication () = default;
};

#endif
