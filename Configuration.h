#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "SubMultiplication.h"

typedef struct Node_n
{
	Operation op;
	Node_n *left, *right;

} Node;

class Configuration
{
    private:
		SubMultiplication *subMultiplications;
		int nSubMultiplications;
		int delay;

    public:
		Configuration();
		Configuration(SubMultiplication*, int, int);
		SubMultiplication* getSubMultiplications();
		int getNSubMultiplications();
		int getDelay();
		void setSubMultiplications(SubMultiplication*);
		void setNSubMultiplications(int);
		void setDelay(int);
		virtual ~Configuration() = default;
};

#endif
