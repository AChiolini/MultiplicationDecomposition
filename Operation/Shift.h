#ifndef SHIFT_H
#define SHIFT_H

#include "Operation.h"

using namespace std;

/* This class represents a shift operation. The information it need to store
 * are shift and latency values.
 */

class Shift : public Operation
{
    private:
	    // Class attributes
        int shift;
        double latency;

    public:
        // Class constructors
        Shift();
        Shift(const Shift&) = default;
        Shift(int);
        Shift(int, double);
        // Class methods
        int getShift();
        void setShift(int);
        void setLatency(double);
        // Inherited methods
        OperationType type() const;
        int requiredOperands();
        double getLatency();
        string description();
        string costDescription();
        string getExpression(vector<string>);
        int outputLength(vector<Link>);
        long long executeOperation(vector<Link>, vector<long long>);
        // Class destructor
        virtual ~Shift() = default;
        // Static methods
        static Shift* castToShift(Operation* operation) { return static_cast<Shift*>(operation); }
        static Shift* castToShift(shared_ptr<Operation> operation) { return static_cast<Shift*>(operation.get()); }
};

#endif
