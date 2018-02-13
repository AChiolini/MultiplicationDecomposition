#include <stdexcept>
#include "Multiplier.h"

using namespace std;

Multiplier::Multiplier()
{
    this->input_length1 = 18;
    this->input_length2 = 18;
    this->input_threshold1 = 6;
    this->input_threshold2 = 6;
    this->latency = 1;
}

Multiplier::Multiplier(int input_length1, int input_length2, int input_threshold1, int input_threshold2, double latency)
{
    setInputLenght1(input_length1);
    setInputLenght2(input_length2);
    setInputThreshold1(input_threshold1);
    setInputThreshold2(input_threshold2);
    setLatency(latency);
}

MultiplicationUnitType Multiplier::type() const
{
    return MULTIPLIER;
}

int Multiplier::getInputLength1()
{
    return this->input_length1;
}

int Multiplier::getInputLength2()
{
    return this->input_length2;
}

int Multiplier::getInputThreshold1()
{
    return this->input_threshold1;
}

int Multiplier::getInputThreshold2()
{
    return this->input_threshold2;
}

double Multiplier::getLatency()
{
    return latency;
}

void Multiplier::setInputLenght1(int input_length1)
{
    if(input_length1 > 1)
    {
        this->input_length1 = input_length1;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input length must be greater than 1");
    }
}

void Multiplier::setInputLenght2(int input_length2)
{
    if(input_length2 > 1)
    {
        this->input_length2 = input_length2;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input length must be greater than 1");
    }
}

void Multiplier::setInputThreshold1(int input_threshold1)
{
    if(input_threshold1 >= 0)
    {
        this->input_threshold1 = input_threshold1;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input threshold must be positive");
    }
}

void Multiplier::setInputThreshold2(int input_threshold2)
{
    if(input_threshold2 >= 0)
    {
        this->input_threshold2 = input_threshold2;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input threshold must be positive");
    }
}

void Multiplier::setLatency(double latency)
{
    if(latency >= 0)
    {
        this->latency = latency;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: latency must be positive");
    }
}

string Multiplier::description()
{
    string s;

    s = "multiplier (" + to_string(this->input_length1);
    s = s + "x" + to_string(this->input_length2) + ")";
    return s;
}
