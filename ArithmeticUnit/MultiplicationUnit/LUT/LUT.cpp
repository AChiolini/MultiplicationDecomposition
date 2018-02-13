#include <stdexcept>
#include "LUT.h"

using namespace std;

LUT::LUT()
{
    this->input_length1 = 18;
    this->input_length2 = 18;
    this->latency = 1;
}

LUT::LUT(int input_length1, int input_length2)
{
    // TO DO USARE SET
    if(input_length1 > 1 && input_length2 > 1)
    {
        this->input_length1 = input_length1;
        this->input_length2 = input_length2;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input length must be greater than 1");
    }
    this->latency = 1;
}

LUT::LUT(int input_length1, int input_length2, double latency)
{
    // TO DO USARE SET
    if(input_length1 > 1 && input_length2 > 1)
    {
        this->input_length1 = input_length1;
        this->input_length2 = input_length2;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input length must be greater than 1");
    }
    if(latency >= 0)
    {
        this->latency = latency;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: latency must be greater or equal to 0");
    }
}

MultiplicationUnitType LUT::type() const
{
    return LUTUNIT;
}

int LUT::getInputLength1()
{
    return this->input_length1;
}

int LUT::getInputLength2()
{
    return this->input_length2;
}

double LUT::getLatency()
{
    return latency;
}

void LUT::setInputLenght1(int input_length1)
{
    if(input_length1 > 0)
    {
        this->input_length1 = input_length1;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input length must be greater than 1");
    }
}

void LUT::setInputLenght2(int input_length2)
{
    if(input_length2 > 0)
    {
        this->input_length2 = input_length2;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input length must be greater than 1");
    }
}

void LUT::setLatency(double latency)
{
    if(latency >= 0)
    {
        this->latency = latency;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: latency must be greater or equal to 0");
    }
}

string LUT::description()
{
    string s;

    s = "LUT (" + to_string(this->input_length1);
    s = s + "x" + to_string(this->input_length2) + ")";
    return s;
}
