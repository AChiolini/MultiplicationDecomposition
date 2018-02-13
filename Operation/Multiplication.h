#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <stdbool.h>
#include <memory>
#include "../ArithmeticUnit/MultiplicationUnit/MultiplicationUnit.h"
#include "../ArithmeticUnit/MultiplicationUnit/LUT/LUT.h"
#include "../ArithmeticUnit/MultiplicationUnit/Multiplier/Multiplier.h"
#include "Operation.h"

using namespace std;

/* This class represents a multiplication operation. The only information it need to
 * store is the multiplication unit used to perform the multiplication (Multiplier or LUT)
 * The latency value is given by the multiplication unit used.
 */

class Multiplication : public Operation
{
    private:
        // Class attribute
        shared_ptr<MultiplicationUnit> multiplication_unit;

    public:
        // Class constructor
        Multiplication(const Multiplication&);
        Multiplication(shared_ptr<MultiplicationUnit>);
        // Class methods
        shared_ptr<MultiplicationUnit> getMultiplicationUnit();
        void setMultiplicationUnit(shared_ptr<MultiplicationUnit>);
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
        virtual ~Multiplication() = default;
        // Static methods
        static Multiplication* castToMultiplication (Operation* operation) { return static_cast<Multiplication*>(operation); }
        static Multiplication* castToMultiplication (shared_ptr<Operation> operation) { return static_cast<Multiplication*>(operation.get()); }
};

#endif
