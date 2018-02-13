#ifndef LUT_H
#define LUT_H

#include <memory>
#include "../MultiplicationUnit.h"

class LUT : public MultiplicationUnit
{
    private:
        int input_length1;
        int input_length2;
        double latency;

    public:
        LUT();
        LUT(const LUT&) = default;
        LUT(int, int);
        LUT(int, int, double);
        MultiplicationUnitType type() const;
        int getInputLength1();
        int getInputLength2();
        double getLatency();
        void setInputLenght1(int);
        void setInputLenght2(int);
        void setLatency(double);
        string description();
        virtual ~LUT() = default;

        static LUT* castToLUT(MultiplicationUnit* unit) { return static_cast<LUT*>(unit); }
        static LUT* castToLUT(shared_ptr<MultiplicationUnit> unit) { return static_cast<LUT*>(unit.get()); }
};

#endif
