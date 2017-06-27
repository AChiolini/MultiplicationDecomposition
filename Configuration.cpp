#include "Configuration.h"

Configuration::Configuration()
{
    this->delay = -1;
    this->nSubMultiplications = 0;
    this->subMultiplications = NULL;
}

Configuration::Configuration(SubMultiplication *subMultiplications, int nSubMultiplications, int delay)
{
    this->subMultiplications = subMultiplications;
    this->nSubMultiplications = nSubMultiplications;
    this->delay = delay;
}

SubMultiplication* Configuration::getSubMultiplications()
{
    return this->subMultiplications;
}

int Configuration::getNSubMultiplication()
{
    return this->nSubMultiplications;
}

int Configuration::getDelay()
{
    return this->delay;
}

void Configuration::setSubMultiplications(SubMultiplication *subMultiplications)
{
    this->subMultiplications = subMultiplications;
}

void Configuration::setNSubMultiplications(int nSubMultiplications)
{
    this->nSubMultiplications = nSubMultiplications;
}

void Configuration::setDelay(int delay)
{
    this->delay = delay;
}
