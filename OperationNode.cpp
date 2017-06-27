#include <stddef.h>
#include "OperationNode.h"

using namespace std;

OperationNode::OperationNode()
{
    //this->
    this->left = NULL;
    this->right = NULL;
}

bool OperationNode::isLeaf()
{
    return false;
}

Node* OperationNode::getLeftChild()
{
    return this->left;
}

Node* OperationNode::getRightChild()
{
    return this->right;
}

void OperationNode::setLeftChild(Node *n)
{
    this->left = n;
}

void OperationNode::setRightChild(Node *n)
{
    this->right = n;
}

OperationNode::~OperationNode()
{
    if (left != NULL)
        delete left;
    if (right != NULL)
        delete right;
}