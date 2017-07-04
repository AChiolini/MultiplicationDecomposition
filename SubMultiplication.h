#ifndef SUBMULTIPLICATION_H
#define SUBMULTIPLICATION_H

#include <stdbool.h>
#include "Multiplier.h"
#include "Operation.h"

class SubMultiplication : public Operation
{
    private:
		Multiplier multiplier;
		bool lut;

    public:
		SubMultiplication();
		SubMultiplication(Multiplier);
		bool isLUT();
		Multiplier getMultiplier();
		void setMultiplier(Multiplier);
		int OperationID() {return 3;};
		~SubMultiplication() = default;
};

#endif
