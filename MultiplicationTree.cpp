#include <stddef.h>
#include <iostream>
#include <string.h>
#include "MultiplicationTree.h"
#include "SubMultiplication.h"
#include "Shift.h"

using namespace std;

MultiplicationTree::MultiplicationTree()
{
    this->root = NULL;
}

MultiplicationTree::MultiplicationTree(OperationNode *root)
{
    this->root = root;
}

OperationNode* MultiplicationTree::getRoot()
{
    return this->root;
}

int MultiplicationTree::getDelay()
{
    return delay(root);
}

void MultiplicationTree::setRoot(OperationNode *root)
{
    this->root = root;
}

int MultiplicationTree::delay(Node* next)
{
    OperationNode *operationNode; 
    OperationNode *ptr;
    SubMultiplication *subMultiplication;
    int nodeDelay, leftDelay, rightDelay;

    if (next == NULL)
    {
        return 0;
    }
    if (next->isLeaf() == true)
    {
        return 0;
    }
    operationNode = static_cast<OperationNode*>(next);
    nodeDelay = 1;
    if (operationNode->getOperation()->getOperationType() == SUBMULTIPLICATION)
    {
        subMultiplication = static_cast<SubMultiplication*>(operationNode->getOperation());
        nodeDelay = subMultiplication->getMultiplier().getDelay();
    }
    else if (operationNode->getOperation()->getOperationType() == SHIFT)
    {
        nodeDelay = 0;
    }
    leftDelay = delay(operationNode->getLeftChild());
    rightDelay = delay(operationNode->getRightChild());
    if (leftDelay > rightDelay)
        return nodeDelay + leftDelay;
    else
        return nodeDelay + rightDelay;
}

char* MultiplicationTree::getExpression()
{
    string s;
    char *cstr;

    s = expression(root);
    cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    return cstr;
}

string MultiplicationTree::expression(Node *next)
{
    OperationNode *operationNode;
    InputNode *inputNode;
    Shift *shift;
    string s;

    if (next == NULL)
    {
        return "";
    }
    if (next->isLeaf() == true)
    {
        inputNode = static_cast<InputNode*>(next);
        if (inputNode->isFirstInput() == true)
        {
            s = "X";
	}
        else
        {
            s = "Y";
        }
        s = s + "[" + to_string(inputNode->getStart()) + "-" + to_string(inputNode->getStart() + inputNode->getLength() - 1) +"]";
    }
    else
    {
        operationNode = static_cast<OperationNode*>(next);
	if (operationNode->getOperation()->getOperationType() == SHIFT)
        {
            shift = static_cast<Shift*>(operationNode->getOperation());
            s = "(2^" + to_string(shift->getK()) + " * ";
            s = s + expression(operationNode->getLeftChild()) + expression(operationNode->getRightChild());
            s = s + ")";
        }
        else
        {
            s = "(" + expression(operationNode->getLeftChild());
            switch (operationNode->getOperation()->getOperationType())
            {
                case ADDITION: s = s + " + ";
                               break;
                case SUBTRACTION: s = s + " - ";
                                  break;
                case SUBMULTIPLICATION: s = s + " * ";
                                        break;
            }
            s = s + expression(operationNode->getRightChild()) + ")";
        }
    }
    return s;
}
