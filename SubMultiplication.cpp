#include <cstdio>
#include "SubMultiplication.h"


SubMultiplication::SubMultiplication()
{
	this->x = 0;
	this->y = 0;
	this->lengthX = 17;
	this->lengthY = 17;
}

SubMultiplication::SubMultiplication (short x, short y, short lengthX, short lengthY)
{
	//TODO controllo valori
	this->x = x;
	this->y = y;
	this->lengthX = lengthX;
	this->lengthY = lengthY;
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
