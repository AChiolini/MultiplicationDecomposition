#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include "../MultiplicationUnit.h"

using namespace std;

class Multiplier : public MultiplicationUnit
{
    private:
        int input_length1;
        int input_length2;
        int input_threshold1;
        int input_threshold2;
        int latency;

    public:
        Multiplier();
        Multiplier(const Multiplier&) = default;
        Multiplier(int, int, int, int, double);
        int getInputLength1();
        int getInputLength2();
        int getInputThreshold1();
        int getInputThreshold2();
        double getLatency();
        void setInputLenght1(int);
        void setInputLenght2(int);
        void setInputThreshold1(int);
        void setInputThreshold2(int);
        void setLatency(double);
        string description();
        virtual ~Multiplier() = default;
};

#endif
