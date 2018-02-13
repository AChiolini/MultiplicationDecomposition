#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include <memory>
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
        MultiplicationUnitType type() const;
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

        static Multiplier* castToMultiplier(MultiplicationUnit* unit) { return static_cast<Multiplier*>(unit); }
        static Multiplier* castToMultiplier(shared_ptr<MultiplicationUnit> unit) { return static_cast<Multiplier*>(unit.get()); }
        static bool isLUTMapped(int x, int y, Multiplier multiplier)
        {
            int min_input, max_input, min_threshold, max_threshold;
            bool result;

            if(multiplier.getInputThreshold1() > multiplier.getInputThreshold2())
            {
                min_threshold = multiplier.getInputThreshold2();
                max_threshold = multiplier.getInputThreshold1();
            }
            else
            {
                min_threshold = multiplier.getInputThreshold1();
                max_threshold = multiplier.getInputThreshold2();
            }
            if(x > y)
            {
                min_input = y;
                max_input = x;
            }
            else
            {
                min_input = x;
                max_input = y;
            }
            if(min_input < min_threshold || max_input < max_threshold)
            {
                result = true;
            }
            else
            {
                result = false;
            }
            return result;
        }
};

#endif
