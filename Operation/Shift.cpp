#include <stdexcept>
#include "Shift.h"

Shift::Shift()
{
    this->shift = 0;
    this->latency = 0;
}

/* Constructor which just requires shift value.
 * Latency is set to 0.
 */

Shift::Shift(int shift)
{
    this->shift = shift;
    this->latency = 0;
}

/* Constructor that requires shift and latency values.
 */

Shift::Shift(int shift, double latency)
{
    this->shift = shift;
    this->latency = latency;
}

int Shift::getShift()
{
    return this->shift;
}

void Shift::setShift(int shift)
{
    this->shift = shift;
}

void Shift::setLatency(double latency)
{
    this->latency = latency;
}

OperationType Shift::type()
{
    return SHIFT;
}

int Shift::requiredOperands()
{
    return 1;
}

double Shift::getLatency()
{
    return this->latency;
}

string Shift::description()
{
    return "shift";
}

string Shift::costDescription()
{
    return "Shift(s)";
}

int Shift::outputLength(vector<Link> operands)
{
    int length1;

    if(operands.size() != 1)
    {
        throw length_error ("Operand for shift must be 1");
    }
    length1 = operands[0].getLength();
    if(operands[0].isSignIncluded() == false)
    {
        length1++;
    }
    return length1 + this->shift;
}

long long Shift::executeOperation(vector<Link> operands, vector<long long> values)
{
    long long value1, copy1, mask1;

    if(operands.size() != 1)
    {
        throw length_error ("Operand for shift must be 1");
    }
    if(values.size() != 1)
    {
        throw length_error ("Value for shift must be 1");
    }
    // Taking the value
    value1 = values[0];
    copy1 = value1;
    // Shifting it to start
    value1 >>= operands[0].getStart();
    // Creating mask for length
    mask1 = 1;
    mask1 <<= operands[0].getLength();
    mask1--;
    // Masking value
    value1 &= mask1;
    // Checking sign extension
    if(operands[0].isSignIncluded() == true)
    {
        copy1 &= 0x8000000000000000;
        copy1 >>= 64 - (operands[0].getLength() + 1);
        value1 |= copy1;
    }
    value1 <<= this->shift;
    return value1;
}
