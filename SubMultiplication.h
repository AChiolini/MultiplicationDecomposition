#ifndef SUBMULTIPLICATION_H
#define SUBMULTIPLICATION_H

#include <stdbool.h>
#include "Multiplier.h"

class SubMultiplication
{
    private:
	short x;
	short y;
	short lengthX;
	short lengthY;
	Multiplier *multiplier;

    public:
	SubMultiplication(short, short, short, short, Multiplier*);
	short getX();
	short getY();
	short getLengthX();
	short getLengthY();
	Multiplier* getMultiplier();
	void setX(short);
	void setY(short);
	void setLengthX(short);
	void setLengthY(short);
	void setMultiplier(Multiplier*);
	virtual ~SubMultiplication() = default;
};

#endif
