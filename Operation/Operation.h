#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <vector>
#include "../Link/Link.h"

using namespace std;

enum OperationType
{
    ADDITION = 0,
    MULTIPLICATION,
    AND,
    OR,
    SHIFT,
    COMPLEMENT2,
    FANOUT,
};

class Operation 
{
    public:
        virtual OperationType type() = 0;
        virtual int requiredOperands() = 0;
        virtual double getLatency() = 0;
        virtual string description() = 0;
        virtual string costDescription() = 0;
        virtual int outputLength(vector<Link>) = 0;
        virtual long long executeOperation(vector<Link>, vector<long long>) = 0;
        virtual ~Operation() = default;
};

#endif
