#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include "../MultiplicationUnit.h"

using namespace std;

class Multiplier : public MultiplicationUnit
{
    private:
        int input_length1;
        int input_length2;
        int output_threshold;
        int latency;

    public:
        Multiplier();
        Multiplier(const Multiplier&) = default;
        Multiplier(int, int, int, double);
        int getInputLength1();
        int getInputLength2();
        int getOutputThreshold();
        double getLatency();
        void setInputLenght1(int);
        void setInputLenght2(int);
        void setOutputThreshold(int);
        void setLatency(double);
        string description();
        virtual ~Multiplier() = default;
};

#endif
