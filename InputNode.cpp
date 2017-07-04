#include "InputNode.h"

InputNode::InputNode()
{
    this->firstInput = true;
    this->start = 0;
    this->length = 32;
}

InputNode::InputNode(bool firstInput, short start, short length)
{
    this->firstInput = firstInput;
    this->start = start;
    this->length = length;
}

bool InputNode::isLeaf()
{
    return true;
}

bool InputNode::isFirstInput()
{
    return this->firstInput;
}

short InputNode::getStart()
{
    return this->start;
}

short InputNode::getLength()
{
    return this->length;
}

void InputNode::setFirstInput(bool firstInput)
{
    this->firstInput = firstInput;
}

void InputNode::setStart(short start)
{
    this->start = start;
}

void InputNode::setLength(short length)
{
    this->length = length;
}