#include <iostream>
#include "InputNode.h"

using namespace std;

InputNode::InputNode()
{
    this->first_input = true;
    this->length = 2;
}

InputNode::InputNode(bool first_input)
{
    this->first_input = first_input;
    this->length = 2;
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

string InputNode::getVariableName()
{
    string s;

    if(this->first_input == true)
    {
        s = "X";
    }
    else
    {
        s = "Y";
    }
    return s;
}

NodeType InputNode::type() const
{
    return INPUT;
}

double InputNode::getLatency()
{
    return 0;
}

vector<Node*> InputNode::getNodes()
{
    vector<Node*> nodes;

    nodes.push_back(this);
    return nodes;
}

long long InputNode::executeNode(long long input1, long long input2)
{
    if(this->first_input == true)
    {
        return input1;
    }
    else
    {
        return input2;
    }
}
