#include <stddef.h>
#include "OperationNode.h"
#include "Addition.h"

using namespace std;

OperationNode::OperationNode()
{
    this->operation = Addition();
    this->shift = 0;
    this->left = NULL;
    this->right = NULL;
}

OperationNode::OperationNode(Operation operation)
{
    this->operation = operation;
    this->shift = 0;
    this->left = NULL;
    this->right = NULL;
}

bool OperationNode::isLeaf()
{
    return false;
}

Operation OperationNode::getOperation()
{
    return this->operation;
}

void OperationNode::setOperation(Operation operation)
{
    this->operation = operation;
}

Node* OperationNode::getLeftChild()
{
    return this->left;
}

Node* OperationNode::getRightChild()
{
    return this->right;
}

int OperationNode::getShift()
{
    return this->shift;
}

void OperationNode::setLeftChild(Node *n)
{
    this->left = n;
}

void OperationNode::setRightChild(Node *n)
{
    this->right = n;
}

void OperationNode::setShift(int shift)
{
    this->shift = shift;
}

OperationNode::~OperationNode()
{
    if (left != NULL)
        delete left;
    if (right != NULL)
        delete right;
}