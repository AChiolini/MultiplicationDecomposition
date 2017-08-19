#ifndef KARATSUBAOFMAN2_H
#define KARATSUBAOFMAN2_H

#include "Multiplication.h"
#include "Multiplier.h"

using namespace std;

/*****************************************************************************/
/* Class that provides multiplication trees following the Karatsuba-Ofman    */
/* idea. Multiplication trees follow the two-part splitting.                 */
/*****************************************************************************/

class KaratsubaOfman2 : public Multiplication
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree dispose(short, short, Multiplier);

    public: 
        KaratsubaOfman2(vector<Multiplier>);
        vector <MultiplicationTree> dispositions(short, short);
        virtual ~KaratsubaOfman2() = default;
};

#endif
