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
    SHIFT,
    COMPLEMENT2,
    FANOUT,
};

class Operation 
{
    public:
        virtual OperationType type() const = 0;
        virtual int requiredOperands() = 0;
        virtual double getLatency() = 0;
        virtual string description() = 0;
        virtual string costDescription() = 0;
        virtual string getExpression(vector<string>) = 0;
        virtual int outputLength(vector<Link>) = 0;
        virtual long long executeOperation(vector<Link>, vector<long long>) = 0;
        virtual ~Operation() = default;

        static void checkLinks(vector<Link> operands)
        {
            int i;

            for(i = 0; i < operands.size(); i++)
            {
                if(operands[i].getNode()->getLength() < operands[i].getStart() + operands[i].getLength())
                {
                    throw invalid_argument("Link length out of range");
                }
            }
        }
};

#endif
