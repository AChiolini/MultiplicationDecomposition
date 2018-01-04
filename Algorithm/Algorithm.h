#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "../MultiplicationTree/MultiplicationTree.h"

class Algorithm
{
    public:
        virtual vector <MultiplicationTree> dispositions (int, int) = 0;
        virtual ~Algorithm () = default;
};

#endif
