#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "SubMultiplication.h"

class Configuration
{
    private:
	SubMultiplication *subMultiplications;
	int nSubMultiplications;
	int delay;

    public:
	Configuration(SubMultiplication*, int, int);
	SubMultiplication* getSubMultiplications();
	int getNSubMultiplication();
	int getDelay();
	void setSubMultiplications(SubMultiplication*);
	void setNSubMultiplications(int);
	void setDelay(int);
	virtual ~Configuration() = default;
};

#endif
