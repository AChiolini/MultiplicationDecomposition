#ifndef MULTIPLICATIONUNIT_H
#define MULTIPLICATIONUNIT_H

#include <string>

using namespace std;

enum MultiplicationUnitType
{
    MULTIPLIER = 0,
    LUTUNIT,
};

class MultiplicationUnit
{        
    public:
        virtual MultiplicationUnitType type() const = 0;
        virtual int getInputLength1() = 0;
        virtual int getInputLength2() = 0;
        virtual double getLatency() = 0;
        virtual void setInputLenght1(int) = 0;
        virtual void setInputLenght2(int) = 0;
        virtual void setLatency(double) = 0;
        virtual string description() = 0;
        //virtual MultiplicationUnitType type() = 0;
        virtual ~MultiplicationUnit() = default;
};

#endif
