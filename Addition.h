#ifndef ADDITION_H
#define ADDITION_H

#include "Operation.h"

class Addition : public Operation
{
    public:
    	int OperationID() {return 1;};
        ~Addition() = default;
};

#endif