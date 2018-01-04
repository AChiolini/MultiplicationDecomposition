#ifndef LUT_H
#define LUT_H

#include "../MultiplicationUnit.h"

class LUT : public MultiplicationUnit
{
    private:
        int input_length1;
        int input_length2;
        double latency;

    public:
        LUT();
        LUT(int, int);
        LUT(int, int, double);
        int getInputLength1();
        int getInputLength2();
        double getLatency();
        void setInputLenght1(int);
        void setInputLenght2(int);
        void setLatency(double);
        string description();
        virtual ~LUT() = default;
};

#endif
