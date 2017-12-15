#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "Operation.h"

class Subtraction : public Operation
{
    public:
        OperationType type() {return SUBTRACTION;};
        virtual ~Subtraction() = default;
};

#endif
