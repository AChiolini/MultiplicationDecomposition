#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "Operation.h"

class Subtraction : public Operation
{
    public:
        int OperationID() {return 2;};
        ~Subtraction() = default;
};

#endif