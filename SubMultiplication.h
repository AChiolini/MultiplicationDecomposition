#ifndef SUBMULTIPLICATION_H
#define SUBMULTIPLICATION_H

#include <stdbool.h>
#include "Multiplier.h"
#include "Operation.h"

class SubMultiplication : public Operation
{
    private:
        int length;
        Multiplier multiplier;
        bool lut;

    public:
        SubMultiplication();
        SubMultiplication(Multiplier);
        bool isLUT();
        Multiplier getMultiplier();
        int getLengthOperation();
        void setMultiplier(Multiplier);
        OperationType getOperationType() {return SUBMULTIPLICATION;};
        virtual ~SubMultiplication() = default;
};

#endif
