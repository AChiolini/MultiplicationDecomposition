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
    long long in1, in2;
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
    in1 = 5;
    in2 = -5;
    //Karatsuba-Ofman multiplication;
    multiplications.push_back(new KaratsubaOfman(multipliers));
    //Standard Tiling
    multiplications.push_back(new StandardTiling(multipliers));
    //Proposed Tiling
    multiplications.push_back(new ProposedTiling(multipliers));
    for (j = 0; j < multiplications.size(); j++)
    {
        multiplicationTrees = (multiplications[j])->dispositions(32, 32);
        for (i = 0; i < multiplicationTrees.size(); i++)
        {
            cout << multiplicationTrees[i].getDescription() << endl;
            cout << "Expression: " << multiplicationTrees[i].getExpression() << endl;
            cout << "Delay: " << multiplicationTrees[i].getDelay() << endl;
            cout << "Expected value: " << (in1 * in2) << endl;
            cout << "Obtained value: " << multiplicationTrees[i].executeMultiplication(in1, in2) << endl;
        }
    }
}
