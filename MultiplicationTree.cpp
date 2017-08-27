#include <stddef.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include "MultiplicationTree.h"
#include "SubMultiplication.h"
#include "Shift.h"

using namespace std;

/*****************************************************************************/
/* Default constructor which set the tree to NULL.                           */
/*****************************************************************************/

MultiplicationTree::MultiplicationTree()
{
    this->root = nullptr;
    this->description = "";
}

/*****************************************************************************/
/* Constructor that required the root operation node of the tree and a       */
/* description.                                                              */
/*****************************************************************************/

MultiplicationTree::MultiplicationTree(shared_ptr<OperationNode> root, string description)
{
    this->root = root;
    this->description = description;
}

/*****************************************************************************/
/* GetRoot method                                                            */
/*****************************************************************************/

shared_ptr<OperationNode> MultiplicationTree::getRoot()
{
    return this->root;
}

/*****************************************************************************/
/* GetDescription method                                                     */
/*****************************************************************************/

string MultiplicationTree::getDescription()
{
    return this->description;
}

/*****************************************************************************/
/* Method that returns the delay of the tree, which is the sum of the delay  */
/* of the components on the longest path of the computation.                 */
/*****************************************************************************/

int MultiplicationTree::getDelay()
{
    return delay(root);
}

/*****************************************************************************/
/* SetRoot method                                                            */
/*****************************************************************************/

void MultiplicationTree::setRoot(shared_ptr<OperationNode> root)
{
    this->root = root;
}

/*****************************************************************************/
/* SetDescription method                                                     */
/*****************************************************************************/

void MultiplicationTree::setDescription(string description)
{
    this->description = description;
}

/*****************************************************************************/
/* Recursive method that calculates the delay of the tree.                   */
/*****************************************************************************/

int MultiplicationTree::delay(shared_ptr<Node> next)
{
    OperationNode *operationNode; 
    OperationNode *ptr;
    SubMultiplication *subMultiplication;
    int nodeDelay, leftDelay, rightDelay;

    if (next == nullptr)
    {
        return 0;
    }
    if (next->isLeaf() == true)
    {
        return 0;
    }
    operationNode = static_cast<OperationNode*>(next.get());
    nodeDelay = 1;
    if (operationNode->getOperation()->getOperationType() == SUBMULTIPLICATION)
    {
        subMultiplication = static_cast<SubMultiplication*>(operationNode->getOperation().get());
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

/*****************************************************************************/
/* Method that returns the string of the mathematical expression of the tree.*/
/*****************************************************************************/

string MultiplicationTree::getExpression()
{
    return expression(root);
}

/*****************************************************************************/
/* Recursive method that construct the mathematical expression of the tree.  */
/*****************************************************************************/

string MultiplicationTree::expression(shared_ptr<Node> next)
{
    OperationNode *operationNode;
    InputNode *inputNode;
    Shift *shift;
    string s;

    if (next == nullptr)
    {
        return "";
    }
    if (next->isLeaf() == true)
    {
        inputNode = static_cast<InputNode*>(next.get());
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
        operationNode = static_cast<OperationNode*>(next.get());
	if (operationNode->getOperation()->getOperationType() == SHIFT)
        {
            shift = static_cast<Shift*>(operationNode->getOperation().get());
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

/*****************************************************************************/
/* Method that returns the cost in term of components for the multiplication.*/
/*****************************************************************************/

string MultiplicationTree::getCost()
{
    vector<OperationNode*> operations;
    vector<string> description;
    vector<int> quantities;
    string s, singleDescription;
    SubMultiplication *multiplication;
    Multiplier multiplier;
    int i, j;
    bool found;

    operations = cost(root);
    for (i = 0; i < operations.size(); i++)
    {
        switch(operations[i]->getOperation()->getOperationType())
        {
            case ADDITION: singleDescription = "Addition(s)";
                           break;
            case SUBTRACTION: singleDescription = "Subtraction(s)";
                              break;
            case SUBMULTIPLICATION: multiplication = static_cast<SubMultiplication*>(operations[i]->getOperation().get());
                                    singleDescription = "Multiplication(s) with ";
                                    if (multiplication->isLUT() == true)
                                    {
                                        singleDescription = singleDescription + "LUT";
                                    }
                                    else
                                    {
                                        multiplier = multiplication->getMultiplier();
                                        singleDescription = singleDescription + "Multiplier (" + to_string(multiplier.getInputLenght1()) + "x";
                                        singleDescription = singleDescription + to_string(multiplier.getInputLenght2()) + ")";
                                    }
                                    break;
            case SHIFT: singleDescription = "Shift(s)";
                        break;
        }
        found = false;
        for (j = 0; j < description.size() && found == false; j++)
        {
            if (description[j].compare(singleDescription) == 0)
            {
                found = true;
                quantities[j]++;
            }
        }
        if (found == false)
        {
            description.push_back(singleDescription);
            quantities.push_back(1);
        }
    }
    s = "";
    for (i = 0; i < description.size(); i++)
    {
        s = s + to_string(quantities[i]) + " " + description[i];
        if (i + 1 != description.size())
        {
            s = s + ", ";
        }
    }
    return s;
}

/*****************************************************************************/
/* Recursive method that construct the cost string for the multiplication.   */
/*****************************************************************************/

vector<OperationNode*> MultiplicationTree::cost(shared_ptr<Node> next)
{
    vector<OperationNode*> operations, childOperations;
    OperationNode *operationNode;
    int i;

    if (next == nullptr)
    {
        return operations;
    }
    if (next->isLeaf() == false)
    {
        operationNode = static_cast<OperationNode*>(next.get());
        operations.push_back(operationNode);
        childOperations = cost(operationNode->getLeftChild());
        for (i = 0; i < childOperations.size(); i++)
        {
            if(find(operations.begin(), operations.end(), childOperations[i]) == operations.end())
            {
                operations.push_back(childOperations[i]);
            }
        }
        childOperations = cost(operationNode->getRightChild());
        for (i = 0; i < childOperations.size(); i++)
        {
            if(find(operations.begin(), operations.end(), childOperations[i]) == operations.end())
            {
                operations.push_back(childOperations[i]);
            }
        }
    }
    return operations;
}

long long MultiplicationTree::executeMultiplication(long long input1, long long input2)
{
    return execute(root, input1, input2);
}

long long MultiplicationTree::execute(shared_ptr<Node> next, long long input1, long long input2)
{
    OperationNode *operationNode;
    InputNode *inputNode;
    Shift *shift;
    long long input, andMask;
    int i, sign;

    if (next == nullptr)
    {
        return 0;
    }
    if (next->isLeaf() == true)
    {
        inputNode = static_cast<InputNode*>(next.get());
        if (inputNode->isFirstInput() == true)
        {
            input = input1;
	}
        else
        {
            input = input2;
        }
        if (input < 0)
        {
            sign = -1;
            input = input * -1;
        }
        else
        {
            sign = 1;
        }
        andMask = 1;
        andMask <<= (inputNode->getLength());
        andMask--;
        input >>= inputNode->getStart();
        input &= andMask;
        input = input * sign;
    }
    else
    {
        operationNode = static_cast<OperationNode*>(next.get());
	if (operationNode->getOperation()->getOperationType() == SHIFT)
        {
            shift = static_cast<Shift*>(operationNode->getOperation().get());
            input = execute(operationNode->getLeftChild(), input1, input2) + execute(operationNode->getRightChild(), input1, input2);
            input <<= shift->getK();
        }
        else
        {
            switch (operationNode->getOperation()->getOperationType())
            {
                case ADDITION: input = execute(operationNode->getLeftChild(), input1, input2) + execute(operationNode->getRightChild(), input1, input2);
                               break;
                case SUBTRACTION: input = execute(operationNode->getLeftChild(), input1, input2) - execute(operationNode->getRightChild(), input1, input2);
                                  break;
                case SUBMULTIPLICATION: input = execute(operationNode->getLeftChild(), input1, input2) * execute(operationNode->getRightChild(), input1, input2);
                                        break;
            }

        }
    }
    return input;
}
