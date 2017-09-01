#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "Operation.h"

class Subtraction : public Operation
{
    private:
        int length;

    public:
        Subtraction();
        int getLengthOperation();
        OperationType getOperationType() {return SUBTRACTION;};
        virtual ~Subtraction() = default;
};

#endif
