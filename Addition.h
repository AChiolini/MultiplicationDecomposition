#ifndef ADDITION_H
#define ADDITION_H

#include "Operation.h"

class Addition : public Operation
{
    public:
    	OperationType getOperationType() {return ADDITION;};
        virtual ~Addition() = default;
};

#endif
