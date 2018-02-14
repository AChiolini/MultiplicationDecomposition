#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "OperationNode.h"
#include "InputNode.h"

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

NodeType OperationNode::type() const
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

void OperationNode::substituteLeaves(shared_ptr<Node> input1, shared_ptr<Node> input2)
{
    int i;
    InputNode *input;
    OperationNode *operation;

    for(i = 0; i < this->operands.size(); i++)
    {
        if(this->operands[i].getNode()->type() == INPUT)
        {
            input = InputNode::castToInputNode(operands[i].getNode());
            if(input->isFirstInput() == true)
            {
                operands[i].setNode(input1);
                cout << "Input 1 incontrato" << endl;
            }
            else
            {
                operands[i].setNode(input2);
                //cout << input2.use_count() << endl;
            }
        }
        else
        {
            operation = OperationNode::castToOperationNode(operands[i].getNode());
            operation->substituteLeaves(input1, input2);
        }
    }
}

void OperationNode::shiftLinksOperands(int s1, int s2)
{
    int i;
    InputNode *input;
    OperationNode *operation;

    for(i = 0; i < this->operands.size(); i++)
    {
        if(this->operands[i].getNode()->type() == INPUT)
        {
            input = InputNode::castToInputNode(operands[i].getNode());
            if(input->isFirstInput() == true)
            {
                operands[i].setStart(operands[i].getStart() + s1);
            }
            else
            {
                operands[i].setStart(operands[i].getStart() + s2);
            }
        }
        else
        {
            operation = OperationNode::castToOperationNode(operands[i].getNode());
            operation->shiftLinksOperands(s1, s2);
        }
    }
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


