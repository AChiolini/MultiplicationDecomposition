#include <vector>
#include <fstream>
#include <iostream>
#include "Multiplication.h"
#include "StandardTiling.h"
#include "KaratsubaOfman.h"

using namespace std;

int main ()
{
    int i, delay, nMultipliers;
    short input1, input2, minInput1, minInput2;
    MultiplicationTree *ptr;
    vector <Multiplier> multipliersVec;
    vector <Multiplication*> multiplications;
    vector <MultiplicationTree> multiplicationTrees;
    Multiplier *multipliers;
    ifstream infile("multipliers");

    //Creating multipliers
    nMultipliers = 0;
    while (infile >> input1 >> input2 >> minInput1 >> minInput2 >> delay)
    {	
        try
        {
            multipliersVec.push_back(Multiplier (input1, input2, minInput1, minInput2, delay));		
        }
        catch (const invalid_argument& e)
        {
            cerr << e.what() << endl;
        }
    }
    nMultipliers = multipliersVec.size();
    if (nMultipliers > 0)
    	multipliers = &multipliersVec[0];
    //Karatsuba-Ofman multiplication;
    multiplications.push_back(new KaratsubaOfman(multipliers, nMultipliers));
    multiplicationTrees = (multiplications[0])->dispositions(32, 32);
    for (i = 0; i < multiplicationTrees.size(); i++)
    {
        cout << multiplicationTrees[i].getDescription() << endl;
        cout << "Expression: " << multiplicationTrees[i].getExpression() << endl;
        cout << "Delay: " << multiplicationTrees[i].getDelay() << endl;
    }

    /*tmp3 = new StandardTiling(multipliers, nMultipliers);
    ptr = tmp3->dispositions(48, 51, &n);
    for (i = 0; i < n; i++)
    {
        cout << "Delay: " << ptr[i].getDelay() << endl;
        cout << ptr[i].getExpression() << endl;
        cout << "FATTO" << endl;
    }*/
}
