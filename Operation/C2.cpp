#include <stdexcept>
#include "C2.h"

C2::C2()
{
    this->overflow = false;
    this->latency = 0;
}

/* Constructor which just requires the overflow value.
 * Latency is set to 0.
 */

C2::C2(bool overflow)
{
    this->overflow = overflow;
    this->latency = 0;
}

/* Constructor that requires overflow and latency values.
 */

C2::C2(bool overflow, double latency)
{
    this->overflow = overflow;
    this->latency = latency;
}

bool C2::isOverflow()
{
    return this->overflow;
}

void C2::setOverflow(bool overflow)
{
    this->overflow = overflow;
}

void C2::setLatency(double latency)
{
    this->latency = latency;
}

OperationType C2::type() const
{
    return COMPLEMENT2;
}

int C2::requiredOperands()
{
	return 1;
}

double C2::getLatency()
{
	return this->latency;
}

string C2::description()
{
    return "two's complement";
}

string C2::costDescription()
{
    return "Two's complement(s)";
}

string C2::getExpression(vector<string> operands_names)
{
    string s;

    if(operands_names.size() != 1)
    {
        throw invalid_argument ("Operand for two's complement must be 1");
    }
    s = "-" + operands_names[0];
    return s;
}

int C2::outputLength(vector<Link> operands)
{
    int length1;

    if(operands.size() != 1)
    {
        throw invalid_argument ("Operand for two's complement must be 1");
    }
    Operation::checkLinks(operands);
    length1 = operands[0].getLength();
    if(operands[0].isSignIncluded() == false)
    {
        length1++;
    }
    if(this->overflow == true)
    {
        length1++;
    }
    return length1;
}

long long C2::executeOperation(vector<Link> operands, vector<long long> values)
{
    long long value1, copy1, mask1, sign_bit;
    int lenght1, shift_value;

    if(operands.size() != 1)
    {
        throw invalid_argument ("Operand for two's complement must be 1");
    }
    Operation::checkLinks(operands);
    if(values.size() != 1)
    {
        throw invalid_argument ("Value for two's complement must be 1");
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
    	shift_value = (operands[0].getLength() - 1);
    	sign_bit = 1;
    	sign_bit <<= shift_value;
        copy1 &= sign_bit;
        copy1 <<= 64 - operands[0].getLength();
        copy1 >>= 64 - (operands[0].getLength() + 1);
        value1 |= copy1;
    }
    value1 = ~value1;
    value1 = value1 + 1;
    return value1;
}
