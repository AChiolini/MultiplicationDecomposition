#include <stddef.h>
#include <iostream>
#include "OperationNode.h"
#include "Addition.h"
#include "Shift.h"
#include "SubMultiplication.h"

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

OperationNode::OperationNode(shared_ptr<Operation>operation, shared_ptr<Node> left, shared_ptr<Node> right)
{
    this->operation = operation;
    this->left = left;
    this->right = right;
}

int OperationNode::getOutputLength()
{
    Shift *shift;
    SubMultiplication *subMultiplication;
    Multiplier multiplier;
    int outputLength, leftLength, rightLength;

    outputLength = -1;
    if (this->left != nullptr || this->right != nullptr)
    {
        if (operation->getOperationType() == SHIFT)
        {
            if (this->left != nullptr)
            {
                leftLength = left->getOutputLength();
                if (leftLength != -1)
                {
                    shift = static_cast<Shift*>(operation.get());
                    outputLength = left->getOutputLength() + shift->getK();
                }
            }
            else
            {
                rightLength = right->getOutputLength();
                if (rightLength != -1)
                {
                    shift = static_cast<Shift*>(operation.get());
                    outputLength = right->getOutputLength() + shift->getK();
                }
            }
        }
        else
        {
            if (this->left != nullptr && this->right != nullptr)
            {
                leftLength = left->getOutputLength();
                rightLength = right->getOutputLength();
                if (leftLength != -1 && rightLength != -1)
                {
                    if (operation->getOperationType() == SUBTRACTION || operation->getOperationType() == ADDITION)
                    {
                        if (leftLength > rightLength)
                        {
                            outputLength = leftLength + 1;
                        }
                        else
                        {
                            outputLength = rightLength + 1;
                        }
                    }
                    else
                    {
                        subMultiplication = static_cast<SubMultiplication*>(operation.get());
                        if (subMultiplication->isLUT() == false)
                        {
                            multiplier = subMultiplication->getMultiplier();
                            if ((multiplier.getInputLength1() >= leftLength && multiplier.getInputLength2() >= rightLength) \
                            || (multiplier.getInputLength1() >= rightLength && multiplier.getInputLength2() >= leftLength))
                            {
                                outputLength = rightLength + leftLength;
                            }
                        }
                        else
                        {
                            outputLength = rightLength + leftLength;
                        }
                    }
                }
            }
        }
    }
    return outputLength;
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
