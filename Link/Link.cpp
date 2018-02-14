#include "Link.h"
#include "../Node/InputNode.h"
#include "../Node/OperationNode.h"

Link::Link()
{
    this->node = nullptr;
    this->start = -1;
    this->length = -1;
    this->sign_included = true;
}

/* Constructor that only requires the shared pointer to the node.
 * Start and length are set to -1 that means the operation should
 * take the entire bit string as output of the node. Sign is included.
 */

Link::Link(shared_ptr<Node> node)
{
    this->node = node;
    this->start = -1;
    this->length = -1;
    this->sign_included = true;
}

/* Constructor with most of the parameters. The operation should take 
 * 'length' bits from 'node' starting from 'start'. Sign is included.
 */

Link::Link(shared_ptr<Node> node, int start, int length)
{
    this->node = node;
    this->start = start;
    this->length = length;
    this->sign_included = true;
}

/* Constructor with all the parameters. The operation should take 
 * 'length' bits from 'node' starting from 'start'. If sign is 'False'
 * it means that the sign of the operation must be set to 0.
 */

Link::Link(shared_ptr<Node> node, int start, int length, bool sign_included)
{
    this->node = node;
    this->start = start;
    this->length = length;
    this->sign_included = sign_included;
}

shared_ptr<Node> Link::getNode()
{
    return this->node;
}

int Link::getStart()
{
    if (start != -1)
    {
        return this->start;
    }
    else
    {
        return 0;
    }
}

int Link::getLength()
{
    if (length != -1)
    {
        return this->length;
    }
    else
    {
        if (node != nullptr)
        {
            return node->getLength();
        }
        else
        {
            return 0;
        }
    }
}

bool Link::isSignIncluded()
{
    return this->sign_included;
}

void Link::setNode(shared_ptr<Node> node)
{
    this->node = node;
}

void Link::setStart(int start)
{
    this->start = start;
}

void Link::setLength(int length)
{
    this->length = length;
}

void Link::setSignIncluded(bool sign_included)
{
    this->sign_included = sign_included;
}

bool Link::entireLength()
{
    if(this->length == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
