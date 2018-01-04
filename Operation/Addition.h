#ifndef ADDITION_H
#define ADDITION_H

#include "Operation.h"

using namespace std;

/* This class represents an addition operation. The only information it need to
 * store is the latency value. However, the operation must be performed through a
 * digital adder and so it will be possible, if needed, to add an arithmetic unit
 * as adder.
 */

class Addition : public Operation
{
    private:
        // Class attribute
        double latency;

    public:
        // Class constructors
        Addition();
        Addition(double);
        // Class method
        void setLatency(double);
        // Inherited methods
        OperationType type();
        int requiredOperands();
        double getLatency();
        string description();
        string costDescription();
        int outputLength(vector<Link>);
        long long executeOperation(vector<Link>, vector<long long>);
        // Class destructor
        virtual ~Addition() = default;
        // Static methods
        static Addition* castToAddition (Operation* operation) { return static_cast<Addition*>(operation); }
        static Addition* castToAddition (shared_ptr<Operation> operation) { return static_cast<Addition*>(operation.get()); }
};

#endif
