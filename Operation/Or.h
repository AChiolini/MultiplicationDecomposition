#ifndef OR_H
#define OR_H

#include "Operation.h"

using namespace std;

/*
 */

class Or : public Operation
{
    private:
        // Class attributes
        int shift_input1;
        int shift_input2;
        double latency;

    public:
        // Class constructors
        Or();
        Or(int, int);
        Or(int, int, double);
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
        virtual ~Or() = default;
        // Static methods
        static Or* castToOr(Operation* operation) { return static_cast<Or*>(operation); }
        static Or* castToOr(shared_ptr<Operation> operation) { return static_cast<Or*>(operation.get()); }
};

#endif
