#include "KaratsubaOfman.h"
#include "Configuration.h"
#include <vector>
#include "SubMultiplication.h"
#include <math.h>
#include <iostream>

using namespace std;

KaratsubaOfman::KaratsubaOfman(Multiplier *multipliers, int nMultipliers)
{
    this->multipliers = multipliers;
    this->nMultipliers = nMultipliers;
}

Configuration* KaratsubaOfman::dispositions(short lengthX, short lengthY, int *nDispositions)
{
    vector <Configuration> configurations;
    int i;

    for(i=0; i<nMultipliers; i++)
    {
        if(multipliers[i].getInputLenght1() % 2 == 0 && multipliers[i].getInputLenght2() % 2 == 0)
        {
            configurations.push_back(dispose(lengthX, lengthY, i));
        }
    }
    if (configurations.size() > 0)
    {
        *nDispositions = configurations.size();
        return &configurations[0];
    }
    else
    {
        *nDispositions = 0;
        return 0;
    }
}

Configuration KaratsubaOfman::dispose(short x, short y, int index)
{
    SubMultiplication *s;
    short lx, ly, lm;
    //s = new SubMultiplication(0, 0, x, y, multipliers[index]);
    cout << "Karatsuba" << endl;
    cout << multipliers[index].getInputLenght1() << ", " << multipliers[index].getInputLenght2() << endl;

    if (x == y && multipliers[index].getInputLenght1() == multipliers[index].getInputLenght2() && \
    (multipliers[index].getInputLenght1() * 2) > x && x > multipliers[index].getInputLenght1())
    {
        lm = x/2;
        s = new SubMultiplication(0, 0, lm, lm, multipliers[index]);
    }
    return Configuration(s, (int) 1, (int) 1);
}