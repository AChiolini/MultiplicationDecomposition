#include <stdexcept>
#include "Multiplier.h"

using namespace std;

Multiplier::Multiplier()
{
    this->inputLength1 = 18;
    this->inputLength2 = 18;
    this->minInput1 = 12;
    this->minInput2 = 12;
    this->delay = 1;
}

Multiplier::Multiplier(short inputLength1, short inputLength2, short minInput1, short minInput2, int delay)
{
    if (inputLength1 > 0 && inputLength2 > 0 && minInput1 > 0 && minInput2 > 0)
    {
	this->inputLength1 = inputLength1;
	this->inputLength2 = inputLength2;
	this->minInput1 = minInput1;
	this->minInput2 = minInput2;
    }
    else
	throw invalid_argument ("Error creating multiplier: input length must be greater than 0");
    if (delay > 0)
	this->delay = delay;
    else
	throw invalid_argument ("Error creating multiplier: delay must be greater than 0");
}

short Multiplier::getInputLenght1()
{
    return inputLength1;
}

short Multiplier::getInputLenght2()
{
    return inputLength2;
}

short Multiplier::getMinInput1()
{
    return minInput1;
}

short Multiplier::getMinInput2()
{
    return minInput2;
}

int Multiplier::getDelay()
{
    return delay;
}

void Multiplier::setInputLenght1(short inputLength)
{
    if (inputLength > 0)
	this->inputLength1 = inputLength;
}

void Multiplier::setInputLenght2(short inputLength)
{
    if (inputLength > 0)
	this->inputLength2 = inputLength;
}

void Multiplier::setMinInput1(short minInput)
{
    if (minInput > 0)
	this->minInput1 = minInput;
}

void Multiplier::setMinInput2(short minInput)
{
    if (minInput > 0)
	this->minInput2 = minInput;
}

void Multiplier::setDelay(int delay)
{
    if (delay > 0)
	this->delay = delay;
}
