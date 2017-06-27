#include "InputNode.h"

InputNode::InputNode()
{
    this->xIndex = 0;
    this->yIndex = 0;
}

InputNode::InputNode(short xIndex, short yIndex)
{
    if (xIndex == 0 || xIndex == 1)
        this->xIndex = xIndex;
    else
	    throw invalid_argument ("Error creating InputNode: X Index must be equal to 0 or 1");
    
    if (yIndex == 0 || yIndex == 1)
        this->yIndex = yIndex;
    else
	    throw invalid_argument ("Error creating InputNode: Y Index must be equal to 0 or 1");
}

bool InputNode::isLeaf()
{
    return true;
}

short InputNode::getXIndex()
{
    return this->xIndex;
}

short InputNode::getYIndex()
{
    return this->yIndex;
}

void InputNode::setXIndex(short xIndex)
{
    this->xIndex = xIndex;
}

void InputNode::setYIndex(short yIndex)
{
    this->yIndex = yIndex;
}