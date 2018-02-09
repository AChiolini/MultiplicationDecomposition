#ifndef STANDARDTILING_H
#define STANDARDTILING_H

#include <vector>
#include "Algorithm.h"
#include "../MultiplicationTree/MultiplicationTree.h"
#include "../ArithmeticUnit/MultiplicationUnit/Multiplier/Multiplier.h"

typedef struct score_t
{
	int levels;
	int not_used_multipliers_bits;
	int LUTs_bits;
}Score;

class StandardTiling : public Algorithm
{
    private:
        vector<Multiplier> multipliers;
        bool sign_operations_included;
        MultiplicationTree dispose(int, int, Multiplier);
        MultiplicationTree disposeSquare(int, int, Multiplier);
        MultiplicationTree disposeRectangle(int, int, Multiplier);
        shared_ptr<OperationNode> createTree(vector <shared_ptr<OperationNode>>);
        bool getBestConfiguration(int*, int*, int, int, Multiplier);
        Score configurationScore(int, int, int, int, Multiplier);
        bool isBestScore(Score, Score);

    public: 
        StandardTiling(vector<Multiplier>);
        StandardTiling(vector<Multiplier>, bool);
        vector<MultiplicationTree> dispositions(int, int);
        virtual ~StandardTiling() = default;
};

#endif
