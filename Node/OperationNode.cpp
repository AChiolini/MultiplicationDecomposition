#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "OperationNode.h"

using namespace std;

OperationNode::OperationNode()
{
    this->operation = nullptr;
    this->length = -1;
}

OperationNode::OperationNode(shared_ptr<Operation> operation)
{
    this->operation = operation;
    this->length = -1;
}

OperationNode::OperationNode(shared_ptr<Operation> operation, int length)
{
    this->operation = operation;
    this->length = length;
}

void OperationNode::checkValidity()
{
    string s;
    int required_operands, n_operands;

    n_operands = this->operands.size();
    required_operands = this->operation->requiredOperands();
    if(required_operands != -1 && required_operands != n_operands)
    {
        s = "Operand for " + this->operation->description() + " must be ";
        s = s + to_string(required_operands) + " and not " + to_string(n_operands) + ".";
        throw length_error (s);
    }
}

shared_ptr<Operation> OperationNode::getOperation()
{
    return this->operation;
}

int OperationNode::getLength()
{
    int length, max, sign;

    if(this->length != -1)
    {
        return this->length;
    }
    else
    {
        return this->operation->outputLength(operands);
    }
}

void OperationNode::setOperation(shared_ptr<Operation> operation)
{
    this->operation = operation;
}

void OperationNode::setLength(int length)
{
    this->length = length;
}

void OperationNode::insertOperandFirst(Link operand)
{
    this->operands.insert(this->operands.begin(), operand);
}

void OperationNode::insertOperandLast(Link operand)
{
    this->operands.push_back(operand);
}

void OperationNode::removeOperandAt(int index)
{
    this->operands.erase(this->operands.begin() + index);
}

void OperationNode::clearOperands()
{
    this->operands.clear();
}

Link OperationNode::getOperandAt(int index)
{
    return this->operands[index];
}

string OperationNode::getOperationExpression(vector<Variable> variables)
{
    int i, this_position, pos, j;
    bool found;
    vector<string> operands_names;
    string s;

    this->checkValidity();
    this_position = -1;
    for(i = 0, found = false; i < variables.size() && found == false; i++)
    {
        if(variables[i].ptr == this)
        {
            found = true;
            this_position = i;
        }
    }
    if(this_position == -1)
    {
        throw runtime_error("Operation doesn't have a variable.");
    }
    for(i = 0; i < this->operands.size(); i++)
    {
        pos = -1;
        for(j = 0, found = false; j < variables.size() && found == false; j++)
        {
            if(variables[j].ptr == operands[i].getNode().get())
            {
                found = true;
                pos = j;
            }
        }
        if(pos == -1)
        {
            throw runtime_error("Operands doesn't have a variable.");
        }
        else
        {
            s = variables[pos].name;
            if(operands[i].entireLength() == false)
            {
                s = s + "[" + to_string(operands[i].getStart());
                s = s + ":" + to_string(operands[i].getStart() + operands[i].getLength() - 1) + "]";
            }
            operands_names.push_back(s);
        }
    }
    s = variables[this_position].name + " = " + this->operation->getExpression(operands_names);
    return s;
}

int OperationNode::size()
{
    return this->operands.size();
}

NodeType OperationNode::type()
{
    return OPERATION;
}

double OperationNode::getLatency()
{
    double max, latency;
    int i, n_operands;

    this->checkValidity();
    max = 0;
    n_operands = this->operands.size();
    for(i = 0; i < n_operands; i++)
    {
        latency = this->operands[i].getNode()->getLatency();
        if(latency > max)
        {
            max = latency;
        }
    }
    return max + this->operation->getLatency();
}

vector<Node*> OperationNode::getNodes()
{
    vector<Node*> nodes, returned_nodes;
    int i, j, n_operands;

    this->checkValidity();
    n_operands = this->operands.size();
    for(i = 0; i < n_operands; i++)
    {
        returned_nodes = this->operands[i].getNode()->getNodes();
        for(j = 0; j < returned_nodes.size(); j++)
        {
            if(find(nodes.begin(), nodes.end(), returned_nodes[j]) == nodes.end())
            {
                nodes.push_back(returned_nodes[j]);
            }
        }
    }
    if(find(nodes.begin(), nodes.end(), this) == nodes.end())
    {
        nodes.push_back(this);
    }
    return nodes;
}

long long OperationNode::executeNode(long long input1, long long input2)
{
    vector<long long> values;
    int i, n_operands;

    this->checkValidity();
    n_operands = this->operands.size();
    for(i = 0; i < n_operands; i++)
    {
        values.push_back(this->operands[i].getNode()->executeNode(input1, input2));
    }
    return this->operation->executeOperation(this->operands, values);
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


