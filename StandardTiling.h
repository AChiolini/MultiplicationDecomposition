#ifndef STANDARDTILING_H
#define STANDARDTILING_H

#include "Multiplication.h"
#include "Multiplier.h"
#include "MultiplicationTree.h"
#include <vector>

class StandardTiling : public Multiplication
{
    private:
        vector<Multiplier> multipliers;
        MultiplicationTree dispose(short, short, Multiplier);
        short checkExist (bool, short, short, vector<shared_ptr<InputNode>>);

    public: 
        StandardTiling(vector<Multiplier>);
        vector<MultiplicationTree> dispositions(short, short);
        virtual ~StandardTiling() = default;
};

#endif
