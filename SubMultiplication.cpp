#include <cstdio>
#include <stdexcept>
#include "SubMultiplication.h"

using namespace std;

SubMultiplication::SubMultiplication()
{
    this->lut = true;
}

SubMultiplication::SubMultiplication(Multiplier multiplier)
{
    this->multiplier = multiplier;
    this->lut = false;
}

Multiplier SubMultiplication::getMultiplier()
{
    return this->multiplier;
}

bool SubMultiplication::isLUT()
{
    return this->lut;
}

void SubMultiplication::setMultiplier(Multiplier multiplier)
{
    this->multiplier = multiplier;
}
