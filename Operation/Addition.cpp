#include <stdexcept>
#include "Addition.h"

Addition::Addition()
{
    this->latency = 0;
}

Addition::Addition(double latency)
{
    this->latency = latency;
}

void Addition::setLatency(double latency)
{
    this->latency = latency;
}

OperationType Addition::type() const
{
    return ADDITION;
}

int Addition::requiredOperands()
{
    return 2;
}

double Addition::getLatency()
{
    return this->latency;
}

string Addition::description()
{
    return "addition";
}

string Addition::costDescription()
{
    return "Addition(s)";
}

string Addition::getExpression(vector<string> operands_names)
{
    string s;

    if(operands_names.size() != 2)
    {
        throw length_error ("Operands for addition must be 2");
    }
    s = operands_names[0] + " + " + operands_names[1];
    return s;
}

int Addition::outputLength(vector<Link> operands)
{
    int length1, length2;

    if(operands.size() != 2)
    {
        throw length_error ("Operands for addition must be 2");
    }
    Operation::checkLinks(operands);
    length1 = operands[0].getLength();
    length2 = operands[1].getLength();
    if(operands[0].isSignIncluded() == false)
    {
        length1++;
    }
    if(operands[1].isSignIncluded() == false)
    {
        length2++;
    }
    if(length1 > length2)
    {
        return length1;
    }
    else
    {
        return length2;
    }
}

long long Addition::executeOperation(vector<Link> operands, vector<long long> values)
{
    long long value1, value2, copy1, copy2, mask1, mask2, sign_bit;
    int shift_value;

    if(operands.size() != 2)
    {
        throw length_error ("Operands for addition must be 2");
    }
    Operation::checkLinks(operands);
    if(values.size() != 2)
    {
        throw length_error ("Values for addition must be 2");
    }
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
    if(operands[1].isSignIncluded() == true)
    {
    	shift_value = (operands[1].getLength() - 1);
    	sign_bit = 1;
    	sign_bit <<= shift_value;
        copy2 &= sign_bit;
        copy2 <<= 64 - operands[1].getLength();
        copy2 >>= 64 - (operands[1].getLength() + 1);
        value2 |= copy2;
    }
    return value1 + value2;
}
