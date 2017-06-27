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
    Configuration c;
    int i;

    for(i=0; i<nMultipliers; i++)
    {
        c = dispose(lengthX, lengthY, i);
        if(c.getNSubMultiplications() > 0)
        {
            configurations.push_back(c);
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

    cout << "Karatsuba" << endl;
    cout << multipliers[index].getInputLenght1() << ", " << multipliers[index].getInputLenght2() << endl;

    if (x == y && multipliers[index].getInputLenght1() == multipliers[index].getInputLenght2() && \
    (multipliers[index].getInputLenght1() * 2) > x && x > multipliers[index].getInputLenght1())
    {
        lm = x/2;
        s = new SubMultiplication[3];
        s[0] = SubMultiplication(0, 0, lm - 1, lm - 1, multipliers[index]);
        s[1] = SubMultiplication(lm - 1, lm - 1, x - lm - 2, x - lm - 2, multipliers[index]);
        //Differenze

        //SubMultiplication Differenze

        return Configuration(s, 3, 1);
    }
    return Configuration();
}