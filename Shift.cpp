#include "Shift.h"

Shift::Shift()
{
    this->k = 0;
}

Shift::Shift(short k)
{
    this->k = k;
}

short Shift::getK()
{
    return this->k;
}

void Shift::setK(short k)
{
    this->k = k;
}
