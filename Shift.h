#ifndef SHIFT_H
#define SHIFT_H

#include "Operation.h"

class Shift : public Operation
{
    private:
        short k;

    public:
        Shift();
        Shift(short);
        short getK();
        void setK(short);
        OperationType getOperationType() {return SHIFT;};
        virtual ~Shift() = default;
};

#endif
