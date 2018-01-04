#include <stdexcept>
#include "Multiplier.h"

using namespace std;

Multiplier::Multiplier()
{
    this->input_length1 = 18;
    this->input_length2 = 18;
    this->output_threshold = 24;
    this->latency = 1;
}

Multiplier::Multiplier(int input_length1, int input_length2, int output_threshold, double latency)
{
    //TO DO USARE SET PER EVITARE CODICE IDENTICO
    if(input_length1 > 1 && input_length2 > 1)
    {
        this->input_length1 = input_length1;
        this->input_length2 = input_length2;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: input length must be greater than 1");
    }
    if(output_threshold > 1)
    {
        this->output_threshold = output_threshold;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: output threshold must be greater than 1");
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

int Multiplier::getInputLength1()
{
    return this->input_length1;
}

int Multiplier::getInputLength2()
{
    return this->input_length2;
}

int Multiplier::getOutputThreshold()
{
    return this->output_threshold;
}

double Multiplier::getLatency()
{
    return latency;
}

void Multiplier::setInputLenght1(int input_length1)
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

void Multiplier::setInputLenght2(int input_length2)
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

void Multiplier::setOutputThreshold(int output_threshold)
{
    if(output_threshold > 0)
    {
        this->output_threshold = output_threshold;
    }
    else
    {
        throw invalid_argument ("Error creating multiplier: output threshold must be greater than 1");
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
        throw invalid_argument ("Error creating multiplier: latency must be greater or equal to 0");
    }
}

string Multiplier::description()
{
    string s;

    s = "multiplier (" + to_string(this->input_length1);
    s = s + "x" + to_string(this->input_length2) + ")";
    return s;
}
