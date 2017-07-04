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
        short getK;
        void setK(short);
        ~Shift() = default;
};

#endif