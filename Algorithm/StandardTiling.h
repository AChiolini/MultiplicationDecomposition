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
        MultiplicationTree disposeSquare(int, int, Multiplier);
        MultiplicationTree disposeRectangle(int, int, Multiplier);
        shared_ptr<OperationNode> createTree(vector <shared_ptr<OperationNode>>);
        shared_ptr<OperationNode> addSignedOperation(shared_ptr<OperationNode>, int, int, shared_ptr<InputNode>, shared_ptr<InputNode>);
        bool isLUTMapped(int, int, Multiplier);
        int disposeOnAxe(int*, int*, int, Multiplier);

    public: 
        StandardTiling(vector<Multiplier>);
        vector<MultiplicationTree> dispositions(int, int);
        virtual ~StandardTiling() = default;
};

#endif
