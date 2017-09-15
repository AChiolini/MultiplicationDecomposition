#include "Shift.h"

Shift::Shift()
{
    this->k = 0;
    this->length = -1;
}

Shift::Shift(short k)
{
    this->k = k;
    this->length = -1;
}

short Shift::getK()
{
    return this->k;
}

void Shift::setK(short k)
{
    this->k = k;
}

int Shift::getLengthOperation()
{
    return 1;
}