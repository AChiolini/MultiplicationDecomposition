#ifndef AND_H
#define AND_H

#include "Operation.h"

using namespace std;

/*
 */

class And : public Operation
{
    private:
        // Class attributes
        int shift_input1;
        int shift_input2;
        double latency;

    public:
        // Class constructors
        And();
        And(int, int);
        And(int, int, double);
        // Class methods
        int getShiftInput1();
        int getShiftInput2();
        void setShiftInput1(int);
        void setShiftInput2(int);
        void setLatency(double);
        // Inherited methods
        OperationType type();
        int requiredOperands();
        double getLatency();
        string description();
        string costDescription();
        string getExpression(vector<string>);
        int outputLength(vector<Link>);
        long long executeOperation(vector<Link>, vector<long long>);
        // Class destructor
        virtual ~And() = default;
        // Static methods
        static And* castToAnd(Operation* operation) { return static_cast<And*>(operation); }
        static And* castToAnd(shared_ptr<Operation> operation) { return static_cast<And*>(operation.get()); }
};

#endif
