#include <stddef.h>
#include <iostream>
#include "OperationNode.h"
#include "Addition.h"
#include "SubMultiplication.h"

using namespace std;

shared_ptr<Operation> operation;
shared_ptr<Link> first_operand;
shared_ptr<Link> second_operand;

OperationNode::OperationNode()
{
    this->operation = nullptr;
    this->first_operand = Link();
    this->second_operand = Link();
    this->length = -1;
}

OperationNode::OperationNode(shared_ptr<Operation> operation)
{
    this->operation = operation;
    this->first_operand = Link();
    this->second_operand = Link();
    this->length = -1;
}

OperationNode::OperationNode(shared_ptr<Operation>operation, Link first_operand, Link second_operand)
{
    this->operation = operation;
    this->first_operand = first_operand;
    this->second_operand = second_operand;
    this->length = -1;
}

OperationNode::OperationNode(shared_ptr<Operation>operation, Link first_operand, Link second_operand, int length)
{
    this->operation = operation;
    this->first_operand = first_operand;
    this->second_operand = second_operand;
    this->length = length;
}

shared_ptr<Operation> OperationNode::getOperation()
{
    return this->operation;
}

Link OperationNode::getFirstOperand()
{
    return this->first_operand;
}

Link OperationNode::getSecondOperand()
{
    return this->second_operand;
}

int OperationNode::getLength()
{
    int l1, l2, max, first_sign, second_sign;

    if(this->first_operand.isSignIncluded() == true)
    {
        first_sign = 0;
    }
    else
    {
        first_sign = 1;
    }
    if(this->second_operand.isSignIncluded() == true)
    {
        second_sign = 0;
    }
    else
    {
        second_sign = 1;
    }
    if(this->length != -1)
    {
        return this->length;
    }
    else
    {
        if(first_operand.getNode() != nullptr && second_operand.getNode() != nullptr)
        {
            l1 = first_operand.getLength();
            l2 = second_operand.getLength();
            if(operation->type() == SUBMULTIPLICATION)
            {
                if(first_sign == 1 && second_sign == 1)
                {
                    return l1 + l2 - 1;
                }
                else
                {
                    if(first_sign == 0 && second_sign == 0)
                    {
                        return l1 + l2 + 1;
                    }
                    else
                    {
                        return l1 + l2;
                    }
                }
            }
            else
            {
                if(l1 > l2)
                {
                    max = l1;
                    if(first_sign == 1)
                    {
                        max++;
                    }
                }
                else
                {
                    max = l2;
                    if(second_sign == 1)
                    {
                        max++;
                    }
                }
                return max + 1;
            }
        }
        else
        {
            return 0;
        }
    }
}

void OperationNode::setOperation(shared_ptr<Operation> operation)
{
    this->operation = operation;
}

void OperationNode::setFirstOperand(Link first_operand)
{
    this->first_operand = first_operand;
}

void OperationNode::setSecondOperand(Link second_operand)
{
    this->second_operand = second_operand;
}

void OperationNode::setLength(int length)
{
    this->length = length;
}

NodeType OperationNode::type()
{
    return OPERATION;
}

/*
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

*/


