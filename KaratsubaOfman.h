#ifndef KARATSUBAOFMAN_H
#define KARATSUBAOFMAN_H

#include "Multiplication.h"
#include "Multiplier.h"

using namespace std;

/*****************************************************************************/
/* Class that provides multiplication trees following the Karatsuba-Ofman    */
/* idea. Multiplication trees follow the 2 way split and later on the 3 way  */
/* split will be implemented.                                                */
/*****************************************************************************/

class KaratsubaOfman : public Multiplication
{
    private:
        Multiplier *multipliers;
        int nMultipliers;
        MultiplicationTree dispose(short, short, int);

    public: 
        KaratsubaOfman(Multiplier*, int);
        vector <MultiplicationTree> dispositions(short, short);
        ~KaratsubaOfman() = default;
};

#endif
