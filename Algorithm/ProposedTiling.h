#ifndef PROPOSEDTILING_H
#define PROPOSEDTILING_H

#include "Algorithm.h"
#include "../Operation/Multiplication.h"
#include "../ArithmeticUnit/MultiplicationUnit/Multiplier/Multiplier.h"
#include "../MultiplicationTree/MultiplicationTree.h"
#include "../Node/InputNode.h"
#include <vector>

class ProposedTiling : public Algorithm
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree disposeHorizontal(int, int, Multiplier);
        MultiplicationTree disposeVertical(int, int, Multiplier);
        shared_ptr<OperationNode> makeShift(Link, Link, shared_ptr<OperationNode>);
        bool isLUTMapped(int, int, Multiplier);
        shared_ptr<OperationNode> addSignedOperation(shared_ptr<OperationNode>, int, int, shared_ptr<InputNode>, shared_ptr<InputNode>);


    public: 
        ProposedTiling(vector<Multiplier>);
        vector<MultiplicationTree> dispositions(int, int);
        virtual ~ProposedTiling() = default;
};

#endif
