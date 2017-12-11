#include <iostream>
#include "InputNode.h"

using namespace std;

InputNode::InputNode()
{
    this->firstInput = true;
    this->length = 0;
}

/* Constructor with two parameters:
 * first_input: 'True' if the node is the first operand of the multiplication.
                'False' otherwise.
 * length: the length of the bit string of the operand (Sign included)
 */

InputNode::InputNode(bool first_input, int length)
{
    this->firstInput = first_input;
    this->length = length;
}

bool InputNode::isFirstInput()
{
    return this->firstInput;
}

short InputNode::getLength()
{
    return this->length;
}

void InputNode::setFirstInput(bool first_input)
{
    this->first_input = first_input;
}

void InputNode::setLength(short length)
{
    this->length = length;
}

bool InputNode::type()
{
    return INPUT;
}
