#ifndef STANDARDTILING_H
#define STANDARDTILING_H

#include <vector>
#include "Algorithm.h"
#include "../MultiplicationTree/MultiplicationTree.h"
#include "../Node/InputNode.h"
#include "../ArithmeticUnit/MultiplicationUnit/Multiplier/Multiplier.h"

class StandardTiling : public Algorithm
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree dispose(int, int, Multiplier);
        MultiplicationTree disposeSquareSquare(int, int, Multiplier);
        MultiplicationTree disposeRectangleSquare(int, int, Multiplier);
        MultiplicationTree disposeRectangleRectangle(int, int, Multiplier);
        shared_ptr<OperationNode> createTree(vector <shared_ptr<OperationNode>>);
        bool isLUTMapped(int, int, Multiplier);
        shared_ptr<OperationNode> addSignedOperation(shared_ptr<OperationNode>, int, int, shared_ptr<InputNode>, shared_ptr<InputNode>);

    public: 
        StandardTiling(vector<Multiplier>);
        vector<MultiplicationTree> dispositions(int, int);
        virtual ~StandardTiling() = default;
};

#endif
