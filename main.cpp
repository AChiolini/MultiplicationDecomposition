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
    Multiplication *tmp, *tmp2;
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
    
    tmp = new StandardTiling(multipliers, nMultipliers);
    tmp->dispositions(66, 34, &n);
    tmp2 = new KaratsubaOfman(multipliers, nMultipliers);
    tmp2->dispositions(66, 66, &n);

    int a = -5000;
    a = a>>5;
    cout << a << endl;
    return (0);
}
