#ifndef STANDARDTILING_H
#define STANDARDTILING_H

#include "Algorithm.h"
#include "../MultiplicationTree/MultiplicationTree.h"
#include "../ArithmeticUnit/MultiplicationUnit/Multiplier/Multiplier.h"
#include <vector>

class StandardTiling : public Algorithm
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree dispose(int, int, Multiplier);
        MultiplicationTree disposeSquareSquare(int, int, Multiplier);
        MultiplicationTree disposeRectangleSquare(int, int, Multiplier);
        MultiplicationTree disposeRectangleRectangle(int, int, Multiplier);
        MultiplicationTree createTree(vector <shared_ptr<OperationNode>>, string, int, int);
        //short checkExist (bool, short, short, vector<shared_ptr<InputNode>>);

    public: 
        StandardTiling(vector<Multiplier>);
        vector<MultiplicationTree> dispositions(int, int);
        virtual ~StandardTiling() = default;
};

#endif
