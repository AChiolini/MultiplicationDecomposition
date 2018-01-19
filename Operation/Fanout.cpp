#include <stdexcept>
#include "Fanout.h"

Fanout::Fanout()
{
    this->fan_value = 1;
    this->latency = 0;
}

/*
 */

Fanout::Fanout(int fan_value)
{
    setFanValue(fan_value);
    this->latency = 0;
}

/*
 */

Fanout::Fanout(int fan_value, double latency)
{
    setFanValue(fan_value);
    this->latency = latency;
}

int Fanout::getFanValue()
{
    return this->fan_value;
}

void Fanout::setFanValue(int fan_value)
{
    if(fan_value > 0)
    {
        this->fan_value = fan_value;
    }
    else
    {
        throw invalid_argument("Shift must be greater than 0");
    }
}

void Fanout::setLatency(double latency)
{
    this->latency = latency;
}

OperationType Fanout::type()
{
    return FANOUT;
}

int Fanout::requiredOperands()
{
    return 1;
}

double Fanout::getLatency()
{
    return this->latency;
}

string Fanout::description()
{
    return "fanout";
}

string Fanout::costDescription()
{
    return "Fanout(s)";
}

string Fanout::getExpression(vector<string> operands_names)
{
    string s;

    if(operands_names.size() != 1)
    {
        throw invalid_argument("Operand for fanout must be 1");
    }
    s = operands_names[0] + "fanout of " + to_string(this->fan_value) + " bits";
    return s;
}

int Fanout::outputLength(vector<Link> operands)
{
    int length1;

    if(operands.size() != 1)
    {
        throw invalid_argument("Operand for fanout must be 1");
    }
    if(operands[0].getLength() != 1)
    {
        throw invalid_argument("Impossible to fanout more than 1 bit");
    }
    return this->fan_value;
}

long long Fanout::executeOperation(vector<Link> operands, vector<long long> values)
{
    long long value1, mask1, fanout;
    int i;

    if(operands.size() != 1)
    {
        throw invalid_argument("Operand for shift must be 1");
    }
    if(values.size() != 1)
    {
        throw invalid_argument("Value for shift must be 1");
    }
    if(operands[0].getLength() != 1)
    {
        throw invalid_argument("Impossible to fanout more than 1 bit");
    }
    // Taking the value
    value1 = values[0];
    // Shifting it to start
    value1 >>= operands[0].getStart();
    // Creating mask for length
    mask1 = 1;
    mask1 <<= operands[0].getLength();
    mask1--;
    // Masking value
    value1 &= mask1;
    // Creating fanout
    fanout = 0;
    for(i = 0; i < this->fan_value; i++)
    {
        fanout |= (value1 << i);
    }
    return fanout;
}
