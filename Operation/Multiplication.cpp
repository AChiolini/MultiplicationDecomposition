#include <stdexcept>
#include "Multiplication.h"

Multiplication::Multiplication(shared_ptr<MultiplicationUnit> multiplication_unit)
{
    setMultiplicationUnit(multiplication_unit);
}

shared_ptr<MultiplicationUnit> Multiplication::getMultiplicationUnit()
{
    return this->multiplication_unit;
}

void Multiplication::setMultiplicationUnit(shared_ptr<MultiplicationUnit> multiplication_unit)
{
    if(multiplication_unit != nullptr)
    {
        this->multiplication_unit = multiplication_unit;
    }
    else
    {
        throw invalid_argument ("Multiplication unit can't be null");
    }
}

OperationType Multiplication::type()
{
    return MULTIPLICATION;
}

int Multiplication::requiredOperands()
{
    return 2;
}

double Multiplication::getLatency()
{
    return this->multiplication_unit->getLatency();
}

string Multiplication::description()
{
    return "multiplication";
}

string Multiplication::costDescription()
{
    return "Multiplication(s) with " + this->multiplication_unit->description();
}

string Multiplication::getExpression(vector<string> operands_names)
{
    string s;

    if(operands_names.size() != 2)
    {
        throw length_error ("Operands for multiplication must be 2");
    }
    s = operands_names[0] + " x " + operands_names[1];
    return s;
}

int Multiplication::outputLength(vector<Link> operands)
{
    int length1, length2;

    if(operands.size() != 2)
    {
        throw length_error ("Operands for multiplication must be 2");
    }
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
    return length1 + length2;
}

long long Multiplication::executeOperation(vector<Link> operands, vector<long long> values)
{
    long long value1, value2, copy1, copy2, mask1, mask2;

    if(operands.size() != 2)
    {
        throw length_error ("Operands for multiplication must be 2");
    }
    if(values.size() != 2)
    {
        throw length_error ("Values for multiplication must be 2");
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
        copy1 &= 0x8000000000000000;
        copy1 >>= 64 -(operands[0].getLength() + 1);
        value1 |= copy1;
    }
    if(operands[1].isSignIncluded() == true)
    {
        copy2 &= 0x8000000000000000;
        copy2 >>= 64 -(operands[1].getLength() + 1);
        value2 |= copy2;
    }
    return value1 * value2;
}
