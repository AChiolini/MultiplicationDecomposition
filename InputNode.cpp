#include <iostream>
#include "InputNode.h"

using namespace std;

InputNode::InputNode()
{
    this->first_input = true;
    this->length = 0;
}

/* Constructor with two parameters:
 * first_input: 'True' if the node is the first operand of the multiplication.
                'False' otherwise.
 * length: the length of the bit string of the operand (Sign included)
 */

InputNode::InputNode(bool first_input, int length)
{
    this->first_input = first_input;
    this->length = length;
}

bool InputNode::isFirstInput()
{
    return this->first_input;
}

int InputNode::getLength()
{
    return this->length;
}

void InputNode::setFirstInput(bool first_input)
{
    this->first_input = first_input;
}

void InputNode::setLength(int length)
{
    this->length = length;
}

NodeType InputNode::type()
{
    return INPUT;
}
