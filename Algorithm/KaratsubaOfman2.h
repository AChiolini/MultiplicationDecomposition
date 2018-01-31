#ifndef KARATSUBAOFMAN2_H
#define KARATSUBAOFMAN2_H

#include "Algorithm.h"
#include "../ArithmeticUnit/Multiplier/Multiplier.h"

using namespace std;

/*****************************************************************************/
/* Class that provides multiplication trees following the Karatsuba-Ofman    */
/* idea. Multiplication trees follow the two-part splitting.                 */
/*****************************************************************************/

class KaratsubaOfman2 : public Multiplication
{
    private:
        vector<Multiplier> multipliers;
        vector <MultiplicationTree> dispose(int, int, Multiplier);
        //void substituteLeaves(shared_ptr<Node>, vector<shared_ptr<Node>>, int);

    public: 
        KaratsubaOfman2(vector<Multiplier>);
        vector <MultiplicationTree> dispositions(int, int);
        virtual ~KaratsubaOfman2() = default;
};

#endif
