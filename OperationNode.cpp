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
    return getOutputSpecifications().length;
}

OutSpecs OperationNode::getOutputSpecifications()
{
    Shift *shift;
    SubMultiplication *subMultiplication;
    Multiplier multiplier;
    OutSpecs specs, rspecs, lspecs, shortspecs, longspecs;
    int k;

    specs.length = -1;
    specs.MCS = 0;
    specs.sign = UNDEFINED;
    if (this->left != nullptr || this->right != nullptr)
    {
        if (operation->getOperationType() == SHIFT)
        {
            if (this->left != nullptr)
            {
                lspecs = left->getOutputSpecifications();
                if (lspecs.length != -1)
                {
                    shift = static_cast<Shift*>(operation.get());
                    k = shift->getK();
                    specs = lspecs;
                    specs.MCS = specs.MCS + k;
                    specs.length = specs.length + k;
                }
            }
            else
            {
                rspecs = right->getOutputSpecifications();
                if (rspecs.length != -1)
                {
                    shift = static_cast<Shift*>(operation.get());
                    k = shift->getK();
                    specs = rspecs;
                    specs.MCS = specs.MCS + k;
                    specs.length = specs.length + k;
                }
            }
        }
        else
        {
            if (this->left != nullptr && this->right != nullptr)
            {
                lspecs = left->getOutputSpecifications();
                rspecs = right->getOutputSpecifications();
                if (lspecs.length != -1 && rspecs.length != -1)
                {
                    if (operation->getOperationType() == SUBTRACTION || operation->getOperationType() == ADDITION)
                    {
                        //1) recognize which is the longest bit size
                        if (lspecs.length > rspecs.length)
                        {
                            specs.length = lspecs.length;
                            shortspecs = rspecs;
                            longspecs = lspecs;
                        }
                        else
                        {
                            specs.length = rspecs.length;
                            shortspecs = lspecs;
                            longspecs = rspecs;
                        }
                        //2) the minimun cumulative shift is the lowest between the righ and the left node
                        if (lspecs.MCS > rspecs.MCS)
                        {
                            specs.MCS = rspecs.MCS;
                        }
                        else
                        {
                            specs.MCS = lspecs.MCS;
                        }
                        //3) Sign check     
                        if (rspecs.sign == UNDEFINED || lspecs.sign == UNDEFINED)
                        {
                            specs.sign = UNDEFINED;
                        }
                        else
                        {
                            //Sum between two positive
                            if (operation->getOperationType() == ADDITION && rspecs.sign == POSITIVE && lspecs.sign == POSITIVE)
                            {
                                specs.sign = POSITIVE;
                            }
                            //sum between two negative
                            else if (operation->getOperationType() == ADDITION && rspecs.sign == NEGATIVE && lspecs.sign == NEGATIVE)
                            {
                                specs.sign = NEGATIVE;
                            }
                            //difference between a positive and a negative
                            else if (operation->getOperationType() == SUBTRACTION && lspecs.sign == POSITIVE && rspecs.sign == NEGATIVE)
                            {
                                specs.sign = POSITIVE;
                            }
                            //difference between a negative and a positive
                            else if (operation->getOperationType() == SUBTRACTION && lspecs.sign == NEGATIVE && rspecs.sign == POSITIVE)
                            {
                                specs.sign = NEGATIVE;
                            }
                            else
                            {
                                specs.sign = UNDEFINED;
                            }
                        }
                        //4) if the longest MCS is lower than the length of the other node, than no need to increasi output length, otherwise it may be increasable
                        if (shortspecs.length >= longspecs.MCS)
                        {
                            //Some cases in which the output length should be increased
                            //1) If there is at least 1 undefined the length must be increased
                            if (rspecs.sign == UNDEFINED || lspecs.sign == UNDEFINED)
                            {
                                specs.length++;
                            }
                            else
                            {
                                //Sum between two positive
                                if (operation->getOperationType() == ADDITION && rspecs.sign == POSITIVE && lspecs.sign == POSITIVE)
                                {
                                    specs.length++;
                                }
                                //sum between two negative
                                else if (operation->getOperationType() == ADDITION && rspecs.sign == NEGATIVE && lspecs.sign == NEGATIVE)
                                {
                                    specs.length++;
                                }
                                //difference between a positive and a negative
                                else if (operation->getOperationType() == SUBTRACTION && lspecs.sign == POSITIVE && rspecs.sign == NEGATIVE)
                                {
                                    specs.length++;
                                }
                                //difference between a negative and a positive
                                else if (operation->getOperationType() == SUBTRACTION && lspecs.sign == NEGATIVE && rspecs.sign == POSITIVE)
                                {
                                    specs.length++;
                                }
                            }
                        }
                    }
                    else
                    {
                        subMultiplication = static_cast<SubMultiplication*>(operation.get());
                        // Sign check   
                        if (rspecs.sign == UNDEFINED || lspecs.sign == UNDEFINED)
                        {
                            specs.sign = UNDEFINED;
                        }
                        else
                        {
                            if (rspecs.sign == lspecs.sign)
                            {
                                specs.sign = POSITIVE;
                            }
                            else
                            {
                                specs.sign = NEGATIVE;
                            }
                        }
                        // MCS
                        if (rspecs.MCS > lspecs.MCS)
                        {
                            specs.MCS = lspecs.MCS;
                        }
                        else
                        {
                            specs.MCS = rspecs.MCS;
                        }
                        if (subMultiplication->isLUT() == false)
                        {
                            multiplier = subMultiplication->getMultiplier();
                            if ((multiplier.getInputLength1() >= lspecs.length && multiplier.getInputLength2() >= rspecs.length) \
                            || (multiplier.getInputLength1() >= rspecs.length && multiplier.getInputLength2() >= lspecs.length))
                            {
                                specs.length = rspecs.length + lspecs.length;
                            }
                        }
                        else
                        {
                            specs.length = rspecs.length + lspecs.length;
                        }
                    }
                }
            }
        }
    }
    return specs;
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
