#ifndef PROPOSEDTILING_H
#define PROPOSEDTILING_H

#include "Multiplication.h"
#include "Multiplier.h"
#include "MultiplicationTree.h"
#include "ShiftNode.h"
#include <vector>

class ProposedTiling : public Multiplication
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree disposeHorizontal(short, short, Multiplier);
        MultiplicationTree disposeVertical(short, short, Multiplier);
        shared_ptr<Node> makeShift(Link, Link, shared_ptr<OperationNode>);
        //short checkExist (bool, short, short, vector<shared_ptr<InputNode>>);

    public: 
        ProposedTiling(vector<Multiplier>);
        vector<MultiplicationTree> dispositions(short, short);
        virtual ~ProposedTiling() = default;
};

#endif
