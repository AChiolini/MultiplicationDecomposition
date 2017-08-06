#include <vector>
#include <fstream>
#include <iostream>
#include "Multiplication.h"
#include "StandardTiling.h"
#include "KaratsubaOfman.h"
#include "ProposedTiling.h"

using namespace std;

int main ()
{
    int i, j, delay;
    short input1, input2, minInput1, minInput2;
    MultiplicationTree *ptr;
    vector <Multiplier> multipliers;
    vector <Multiplication*> multiplications;
    vector <MultiplicationTree> multiplicationTrees;

    ifstream infile("multipliers");

    //Creating multipliers
    while (infile >> input1 >> input2 >> minInput1 >> minInput2 >> delay)
    {	
        try
        {
            multipliers.push_back(Multiplier (input1, input2, minInput1, minInput2, delay));		
        }
        catch (const invalid_argument& e)
        {
            cerr << e.what() << endl;
        }
    }
    //Karatsuba-Ofman multiplication;
    multiplications.push_back(new KaratsubaOfman(multipliers));
    //Standard Tiling
    multiplications.push_back(new StandardTiling(multipliers));
    //Proposed Tiling
    multiplications.push_back(new ProposedTiling(multipliers));
    for (j = 0; j < multiplications.size(); j++)
    {
        multiplicationTrees = (multiplications[j])->dispositions(58, 58);
        for (i = 0; i < multiplicationTrees.size(); i++)
        {
            cout << multiplicationTrees[i].getDescription() << endl;
            cout << "Expression: " << multiplicationTrees[i].getExpression() << endl;
            cout << "Delay: " << multiplicationTrees[i].getDelay() << endl;
        }
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
