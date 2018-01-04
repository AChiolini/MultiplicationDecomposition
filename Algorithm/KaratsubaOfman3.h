#ifndef KARATSUBAOFMAN3_H
#define KARATSUBAOFMAN3_H

#include "Multiplication.h"
#include "Multiplier.h"

using namespace std;

/*****************************************************************************/
/* Class that provides multiplication trees following the Karatsuba-Ofman    */
/* idea. Multiplication trees follow the three-part splitting.               */
/*****************************************************************************/

class KaratsubaOfman3 : public Multiplication
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree dispose(short, short, Multiplier);

    public: 
        KaratsubaOfman3(vector<Multiplier>);
        vector <MultiplicationTree> dispositions(short, short);
        virtual ~KaratsubaOfman3() = default;
};

#endif
