#include <stddef.h>
#include "OperationNode.h"
#include "Addition.h"
#include <iostream>

using namespace std;

OperationNode::OperationNode()
{
    this->operation = make_shared<Addition>();
    this->left = nullptr;
    this->right = nullptr;
}

OperationNode::OperationNode(shared_ptr<Operation> operation)
{
    this->operation = operation;
    this->left = nullptr;
    this->right = nullptr;
}

bool OperationNode::isLeaf()
{
    return false;
}

shared_ptr<Operation> OperationNode::getOperation()
{
    return this->operation;
}

void OperationNode::setOperation(shared_ptr<Operation> operation)
{
    this->operation = operation;
}

shared_ptr<Node> OperationNode::getLeftChild()
{
    return this->left;
}

shared_ptr<Node> OperationNode::getRightChild()
{
    return this->right;
}

void OperationNode::setLeftChild(shared_ptr<Node> n)
{
    this->left = n;
}

void OperationNode::setRightChild(shared_ptr<Node> n)
{
    this->right = n;
}
