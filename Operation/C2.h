#ifndef C2_H
#define C2_H

#include "Operation.h"

using namespace std;

/* This class represents a two's complement operation. The information it need to 
 * store are the possibility of overflowing (i.e. if the two's complement is performed
 * from a negative number to a positive one, it's possible to have overflow) and 
 * the latency value.
 */

class C2 : public Operation
{        
    private:
	    // Class attributes
        bool overflow;
        double latency;

    public:
        // Class constructors
        C2();
        C2(bool);
        C2(bool, double);
        // Class methods
        bool isOverflow();
        void setOverflow(bool);
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
        virtual ~C2() = default;
        // Static methods
        static C2* castToC2(Operation* operation) { return static_cast<C2*>(operation); }
        static C2* castToC2(shared_ptr<Operation> operation) { return static_cast<C2*>(operation.get()); }
};

#endif
