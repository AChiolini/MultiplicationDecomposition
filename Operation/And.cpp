#include <stdexcept>
#include "And.h"

And::And()
{
    this->shift_input1 = 0;
    this->shift_input2 = 0;
    this->latency = 0;
}

And::And(int shift_input1, int shift_input2)
{
    setShiftInput1(shift_input1);
    setShiftInput2(shift_input2);
}

And::And(int shift_input1, int shift_input2, double latency)
{
    setShiftInput1(shift_input1);
    setShiftInput2(shift_input2);
    setLatency(latency);
}

int And::getShiftInput1()
{
    return this->shift_input1;
}

int And::getShiftInput2()
{
    return this->shift_input2;
}

void And::setShiftInput1(int shift_input1)
{
    if(shift_input1 >= 0)
    {
        this->shift_input1 = shift_input1;
    }
    else
    {
        throw invalid_argument ("Shift can't be negative");
    }
}

void And::setShiftInput2(int shift_input2)
{
    if(shift_input2 >= 0)
    {
        this->shift_input2 = shift_input2;
    }
    else
    {
        throw invalid_argument ("Shift can't be negative");
    }
}

void And::setLatency(double latency)
{
    this->latency = latency;
}

OperationType And::type() const
{
    return AND;
}

int And::requiredOperands()
{
    return 2;
}

double And::getLatency()
{
    return this->latency;
}

string And::description()
{
    return "and";
}

string And::costDescription()
{
    return "And(s)";
}

string And::getExpression(vector<string> operands_names)
{
    string s;

    if(operands_names.size() != 2)
    {
        throw invalid_argument ("Operands for and must be 2");
    }
    if(this->shift_input1 != 0)
    {
        operands_names[0] = operands_names[0] + "->" + to_string(this->shift_input1);
    }
    if(this->shift_input2 != 0)
    {
        operands_names[1] = operands_names[1] + "->" + to_string(this->shift_input2);
    }
    s = operands_names[0] + " & " + operands_names[1];
    return s;
}

int And::outputLength(vector<Link> operands)
{
    int length1, length2;

    if(operands.size() != 2)
    {
        throw invalid_argument ("Operands for and must be 2");
    }
    Operation::checkLinks(operands);
    length1 = operands[0].getLength();
    length2 = operands[1].getLength();
    if(length1 > length2)
    {
        return length1;
    }
    else
    {
        return length2;
    }
}

long long And::executeOperation(vector<Link> operands, vector<long long> values)
{
    long long value1, value2, copy1, copy2, mask1, mask2, result, min, max, first_bit;
    Link min_operand, max_operand;
    int length1, length2, i, shift_value;

    if(operands.size() != 2)
    {
        throw invalid_argument("Operands for and must be 2");
    }
    Operation::checkLinks(operands);
    if(values.size() != 2)
    {
        throw invalid_argument("Values for and must be 2");
    }
    length1 = operands[0].getLength();
    length2 = operands[1].getLength();
    // Taking the values
    value1 = values[0];
    value2 = values[1];
    copy1 = value1;
    copy2 = value2;
    // Shifting them to start
    value1 >>= operands[0].getStart();
    value2 >>= operands[1].getStart();
    // Creating mask for length
    mask1 = 1;
    mask2 = 1;
    mask1 <<= operands[0].getLength();
    mask2 <<= operands[1].getLength();
    mask1--;
    mask2--;
    // Masking values
    value1 &= mask1;
    value2 &= mask2;
    if(length1 == length2)
    {
        // Just and the two operands
        // First check if shift1 and shift2 are zeroes
        if(this->shift_input1 == 0 && this->shift_input2 == 0)
        {
            result = value1 & value2;
        }
        else
        {
            throw invalid_argument("Impossible to and with undefined bit values");
        }
    }
    else
    {
        // And the smaller operand with the larger one (and with some bits)
        if(length1 > length2)
        {
            if(length2 + this->shift_input2 > length1)
            {
                throw invalid_argument("Impossible to and with undefined bit values");
            }
            if(this->shift_input1 > 0)
            {
                throw invalid_argument("Operands shouldn't be shifted");
            }
            min_operand = operands[1];
            min = values[1];
            max_operand = operands[0];
            max = values[0];
            shift_value = this->shift_input2;
        }
        else
        {
            if(length1 + this->shift_input1 > length2)
            {
                throw invalid_argument("Impossible to and with undefined bit values");
            }
            if(this->shift_input2 > 0)
            {
                throw invalid_argument("Operands shouldn't be shifted");
            }
            min_operand = operands[0];
            min = values[0];
            max_operand = operands[1];
            max = values[1];
            shift_value = this->shift_input1;
        }
        mask1 = 0;
        for(i = 0; i < max_operand.getLength(); i++)
        {
            if(i >= shift_value && i <= shift_value + min_operand.getLength() - 1)
            {
                first_bit = min & 1;
                min >>= 1;
            }
            else
            {
                first_bit = 1;
            }
            first_bit <<= i;
            mask1 |= first_bit;
        }
        result = max & mask1;
    }
    return result;
}
