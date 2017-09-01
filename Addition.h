#ifndef ADDITION_H
#define ADDITION_H

#include "Operation.h"

class Addition : public Operation
{
    private:
        int length;

    public:
        Addition();
        int getLengthOperation();
    	OperationType getOperationType() {return ADDITION;};
        virtual ~Addition() = default;
};

#endif
