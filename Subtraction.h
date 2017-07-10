#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "Operation.h"

class Subtraction : public Operation
{
    public:
        OperationType getOperationType() {return SUBTRACTION;};
        ~Subtraction() = default;
};

#endif
