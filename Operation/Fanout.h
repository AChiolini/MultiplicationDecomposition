#ifndef FANOUT_H
#define FANOUT_H

#include "Operation.h"

using namespace std;

/*
 */

class Fanout : public Operation
{
    private:
	    // Class attributes
        int fan_value;
        double latency;

    public:
        // Class constructors
        Fanout();
        Fanout(const Fanout&) = default;
        Fanout(int);
        Fanout(int, double);
        // Class methods
        int getFanValue();
        void setFanValue(int);
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
        virtual ~Fanout() = default;
        // Static methods
        static Fanout* castToFanout(Operation* operation) { return static_cast<Fanout*>(operation); }
        static Fanout* castToFanout(shared_ptr<Operation> operation) { return static_cast<Fanout*>(operation.get()); }
};

#endif
