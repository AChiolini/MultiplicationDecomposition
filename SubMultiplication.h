#ifndef SUBMULTIPLICATION_H
#define SUBMULTIPLICATION_H

#include <stdbool.h>
#include <memory>
#include "Multiplier.h"
#include "Operation.h"

using namespace std;

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
        void setMultiplier(Multiplier);
        OperationType getOperationType() {return SUBMULTIPLICATION;};
        virtual ~SubMultiplication() = default;

        static SubMultiplication* castToSubMultiplication (Operation* operation) { return static_cast<SubMultiplication*>(operation); }
        static SubMultiplication* castToSubMultiplication (shared_ptr<Operation> operation) { return static_cast<SubMultiplication*>(operation.get()); }
};

#endif
