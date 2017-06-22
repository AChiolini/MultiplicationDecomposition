#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "Multiplier.h"
#include "Configuration.h"

class Multiplication
{
    protected:
		Multiplier *multipliers;
		int nMultipliers;
//		Configuration* standardDisposition (Multiplier*, short, short);
//		void KaratsubaOfman (long long, long long, short, short);

    public:
		Multiplication ();
//		long long multiply(short, long long, short, long long);
		virtual Configuration* dispositions (short, short, int*) = 0;
		virtual ~Multiplication () = default;
};

#endif
