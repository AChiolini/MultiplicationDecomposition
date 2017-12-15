#include "ShiftNode.h"

ShiftNode::ShiftNode()
{
    this->operand = Link();
    this->shift = 0;
}

/* Constructor which just requires the pointer to the node it needs 
 * to be shifted. Shift is set to 0.
 */

ShiftNode::ShiftNode(Link operand)
{
    this->operand = operand;
    this->shift = 0;
}

/* Constructor that requires the pointer to the node it needs 
 * to be shifted and the value of the shift.
 */

ShiftNode::ShiftNode(Link operand, int shift)
{
    this->operand = operand;
    this->shift = shift;
}

Link ShiftNode::getOperand()
{
    return this->operand;
}

int ShiftNode::getShift()
{
    return this->shift;
}

void ShiftNode::setOperand(Link operand)
{
    this->operand = operand;
}

void ShiftNode::setShift(int shift)
{
    this->shift = shift;
}

NodeType ShiftNode::type()
{
    return SHIFT;
}

int ShiftNode::getLength()
{
    if (operand.getNode() != nullptr)
    {
        return operand.getLength() - operand.getStart() + shift;
    }
    else
    {
        return 0;
    } 
}
