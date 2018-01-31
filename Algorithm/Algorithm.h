#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "../MultiplicationTree/MultiplicationTree.h"
#include "../ArithmeticUnit/MultiplicationUnit/Multiplier/Multiplier.h"

class Algorithm
{
    public:
        virtual vector <MultiplicationTree> dispositions (int, int) = 0;
        virtual ~Algorithm () = default;

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
