#include <cstdio>
#include <stdexcept>
#include "SubMultiplication.h"

using namespace std;

SubMultiplication::SubMultiplication()
{
    this->x = 0;
    this->y = 0;
    this->lengthX = 17;
    this->lengthY = 17;
    this->multiplier;
}

SubMultiplication::SubMultiplication(short x, short y,  short lengthX, short lengthY, Multiplier multiplier)
{
    if (x >= 0 && y >= 0)
    {
	this->x = x;
	this->y = y;
    }
    else
	throw invalid_argument ("Error creating submultiplication: input coordinates must be greater or equal to 0");
    if (lengthX > 0 && lengthY > 0)
    {
	this->lengthX = lengthX;
	this->lengthY = lengthY;
    }
    else
	throw invalid_argument ("Error creating submultiplication: input lengths must be greater than 0");
    this->multiplier = multiplier;
}

short SubMultiplication::getX()
{
    return this->x;
}

short SubMultiplication::getY()
{
    return this->y;
}

short SubMultiplication::getLengthX()
{
    return this->lengthX;
}

short SubMultiplication::getLengthY()
{
    return this->lengthY;
}

Multiplier SubMultiplication::getMultiplier()
{
    return this->multiplier;
}

void SubMultiplication::setX(short x)
{
    if (x >= 0)
    {
	this->x = x;
    }
}

void SubMultiplication::setY(short y)
{
    if (y >= 0)
    {
	this->y = y;
    }
}

void SubMultiplication::setLengthX(short length)
{
    if (length > 1)
    {
	this->lengthX = length;
    }
}

void SubMultiplication::setLengthY(short length)
{
    if (length > 1)
    {
	this->lengthY = length;
    }
}

void SubMultiplication::setMultiplier(Multiplier multiplier)
{
    this->multiplier = multiplier;
}
