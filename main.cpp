#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Algorithm/Algorithm.h"
#include "Algorithm/StandardTiling.h"
//#include "KaratsubaOfman2.h"
//#include "KaratsubaOfman3.h"
#include "Algorithm/ProposedTiling.h"

using namespace std;

bool is_number(char*);

int main (int argc, char** argv)
{
    int i, j, delay, input1, input2, output_threshold;
    long long in1, in2;
    int inputLength1, inputLength2, inpu1_threshold, input2_threshold;
    MultiplicationTree *ptr;
    vector <Multiplier> multipliers;
    vector <Algorithm*> algorithms;
    vector <MultiplicationTree> multiplicationTrees;
    ifstream infile("ArithmeticUnit/MultiplicationUnit/multipliers");

    if (argc == 5 && is_number(argv[1]) && is_number(argv[2]) && is_number(argv[3]) && is_number(argv[4]))
    {
        in1 = atoll(argv[3]);
        in2 = atoll(argv[4]);
        inputLength1 = atoi(argv[1]);
        inputLength2 = atoi(argv[2]);
        //Creating multipliers
        while (infile >> input1 >> input2 >> inpu1_threshold >> input2_threshold >> delay)
        {	
            try
            {
                multipliers.push_back(Multiplier (input1, input2, inpu1_threshold, input2_threshold, delay));
            }
            catch (const invalid_argument& e)
            {
                cerr << e.what() << endl;
            }
        }
        //Karatsuba-Ofman two-part splitting
        //algorithms.push_back(new KaratsubaOfman2(multipliers));
        //Karatsuba-Ofman three-part splitting
        //algorithms.push_back(new KaratsubaOfman3(multipliers));
        //Standard Tiling
        algorithms.push_back(new StandardTiling(multipliers));
        //Proposed Tiling
        algorithms.push_back(new ProposedTiling(multipliers));
        for (j = 0; j < algorithms.size(); j++)
        {
            multiplicationTrees = (algorithms[j])->dispositions(inputLength1, inputLength2);
            for (i = 0; i < multiplicationTrees.size(); i++)
            {
                cout << multiplicationTrees[i].getDescription() << endl;
                cout << "Expression: " << multiplicationTrees[i].getExpression() << endl;
                cout << "Delay: " << multiplicationTrees[i].getLatency() << endl;
                cout << "Cost: " << multiplicationTrees[i].getCost() << endl;
                cout << "Expected value: " << in1 * in2 << endl;
                cout << "Obtained value: " << multiplicationTrees[i].executeMultiplication(in1, in2) << endl;
                cout << "Output Length: " << multiplicationTrees[i].getOutputLength() << endl;
                cout << endl;
                cout << endl;
            }
        }
    }
    else
    {
        cout << "usage: <input length 1> <input length 2> <first factor> <second factor>" << endl;
    }
}

bool is_number(char* s)
{
    bool isNumber;
    int i;

    if (s[0] == '\0')
    {
        return false;
    }
    if (s[0] == 45)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
    if (s[i] == '\0')
    {
        return false;
    }
    isNumber = true;
    for (; s[i] != '\0' && isNumber == true; i++)
    {
        if (s[i] < 48 || s[i] > 57)
        {
            isNumber = false;
        }
    }
    return isNumber;
}
