#include "KaratsubaOfman.h"

using namespace std;

KaratsubaOfman::KaratsubaOfman(Multiplier *multipliers, int nMultipliers)
{
    this->multipliers = multipliers;
    this->nMultipliers = nMultipliers;
}

Configuration* KaratsubaOfman::dispositions(short lengthX, short lengthY, int *nDispositions)
{
    vector Configuration configurations;
    int i;

    for(i=0; i<nMultipliers; i++)
    {
        configurations.push_back(dispose(lengthX, lengthY, i));
    }
    if (configurations.size() > 0)
    {
        *nDispositions = configurations.size();
        return &configurations[0];
    }
    else
    {
        *nDispositions = 0;
        return NULL;
    }
}

Configuration KaratsubaOfman::dispose(short x, short y, short index)
{
    
}