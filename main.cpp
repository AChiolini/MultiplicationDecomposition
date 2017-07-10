#include <vector>
#include <fstream>
#include <iostream>
#include "Multiplication.h"
#include "StandardTiling.h"
#include "KaratsubaOfman.h"

using namespace std;

int main ()
{
    /*
    Multiplication mult;
    mult.multiply (66, 0, 34, 0);
    */

    int i, delay, nMultipliers, n;
    short input1, input2, minInput1, minInput2;
    Multiplication *tmp, *tmp2, *tmp3;
    MultiplicationTree *ptr;
    vector <Multiplier> array;
    Multiplier *multipliers;
    ifstream infile("multipliers");

    nMultipliers = 0;
    while (infile >> input1 >> input2 >> minInput1 >> minInput2 >> delay)
    {	
        try
        {
            array.push_back(Multiplier (input1, input2, minInput1, minInput2, delay));		
        }
        catch (const invalid_argument& e)
        {
            cerr << e.what() << endl;
        }
    }
    nMultipliers = array.size();
    if (nMultipliers > 0)
    	multipliers = &array[0];
    
    /*tmp = new StandardTiling(multipliers, nMultipliers);
    tmp->dispositions(66, 34, &n);*/
    tmp2 = new KaratsubaOfman(multipliers, nMultipliers);
    ptr = tmp2->dispositions(32, 32, &n);
    for (i = 0; i < n; i++)
    {
        cout << ptr[i].getDelay() << endl;
    }
    tmp3 = new StandardTiling(multipliers, nMultipliers);
    ptr = tmp3->dispositions(58, 58, &n);
    for (i = 0; i < n; i++)
    {
        cout << ptr[i].getDelay() << endl;
    }
}
