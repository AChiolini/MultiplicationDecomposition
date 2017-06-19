#ifndef MULTIPLIER_H
#define MULTIPLIER_H

class Multiplier
{
    private:
	short inputLength1;
	short inputLength2;
	short minInput1;
	short minInput2;
	int delay;

    public:
	Multiplier();
	Multiplier(short, short, short, short, int);
	short getInputLenght1();
	short getInputLenght2();
	short getMinInput1();
	short getMinInput2();
	int getDelay();
	void setInputLenght1(short);
	void setInputLenght2(short);
	void setMinInput1(short);
	void setMinInput2(short);
	void setDelay(int);
	virtual ~Multiplier() = default;
};

#endif
