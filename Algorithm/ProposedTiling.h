#ifndef PROPOSEDTILING_H
#define PROPOSEDTILING_H

#include "Multiplication.h"
#include "Multiplier.h"
#include "MultiplicationTree.h"
#include <vector>

class ProposedTiling : public Multiplication
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree disposeHorizontal(short, short, Multiplier);
        MultiplicationTree disposeVertical(short, short, Multiplier);
        shared_ptr<OperationNode> makeShift(shared_ptr<InputNode>, shared_ptr<InputNode>, shared_ptr<OperationNode>);
        short checkExist (bool, short, short, vector<shared_ptr<InputNode>>);

    public: 
        ProposedTiling(vector<Multiplier>);
        vector<MultiplicationTree> dispositions(short, short);
        virtual ~ProposedTiling() = default;
};

#endif
