#include <stddef.h>
#include <iostream>
#include <string.h>
#include "MultiplicationTree.h"

using namespace std;

/*****************************************************************************/
/* Default constructor which set the tree to NULL.                           */
/*****************************************************************************/

MultiplicationTree::MultiplicationTree()
{
    this->root = nullptr;
    this->description = "";
    this->lengthX = 0;
    this->lengthY = 0;
}

/*****************************************************************************/
/* Constructor that required the root operation node of the tree and a       */
/* description.                                                              */
/*****************************************************************************/

MultiplicationTree::MultiplicationTree(shared_ptr<OperationNode> root, string description, int lengthX, int lengthY)
{
    this->root = root;
    this->description = description;
    this->lengthX = lengthX;
    this->lengthY = lengthY;
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

int MultiplicationTree::getLatency()
{
    return root->getLatency();
}

int MultiplicationTree::getLengthX()
{
    return lengthX;
}

int MultiplicationTree::getLengthY()
{
    return lengthY;
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

void MultiplicationTree::setLengthX(int lengthX)
{
    this->lengthX = lengthX;
}

void MultiplicationTree::setLengthY(int lengthY)
{
    this->lengthY = lengthY;
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

string MultiplicationTree::expression(shared_ptr<Node>)
{
    /*OperationNode *operationNode;
    InputNode *input_node;
    Shift *shift;
    string s;

    if (next == nullptr)
    {
        return "";
    }
    if (next->type() == INPUT)
    {
        input_node = InputNode::castToInputNode(next);
        if (input_node->isFirstInput() == true)
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
    return s;*/
    string s = "Da fare";
    return s;
}

/*vector<Variable> MultiplicationTree::assignment(shared_ptr<Node> next)
{
    ShiftNode shift_node;
    InputNode input_node;
    OperationNode operation_node;
    vector<Variable> array1, array2, tmp;
    Variable var;
    string s;
    char c;
    int i, n, letter, number;

    if(next == nullptr)
    {
        return array;
    }
    switch(next->type())
    {
        case INPUT: 
            input_node = InputNode::castToInputNode(next);
            if (input_node->isFirstInput() == true)
            {
                s = "X";
	    }
            else
            {
                s = "Y";
            }
            s = s + " - Input";
            var.name = s
            var.ptr = next;
            break;
        case OPERATION: 
            break;
        case SHIFT: 
            break;
        default: 
            total_delay = 0;
            break;
    }

    if(next->type() == INPUT)
    {

    }
    else(next->type() == SHIFT)
    {
        shift_node = ShiftNode::castToShiftNode(next);
        array1 = assignment(shift_node->getOperand().getNode());
        var.name = getVariableName(array1.size() - 2);
        var.ptr = next;
    }
    else
    {
        operation_node = OperationNode::castToOperationNode(next);
        array1 = assignment(operation_node->getFirstOperand().getNode());
        array2 = assignment(operation_node->getSecondOperand().getNode());
        if(array1.size() < array2.size())
        {
            tmp = array1;
            array1 = array2;
            array2 = tmp;
        }
    }
}

string MultiplicationTree::getVariableName(int n)
{
    int number, letter;
    char c;
    string s;

    number = n / 24;
    letter = n % 24;
    if(letter == 24)
    {
        letter = 26;
    }
    c = (char) letter + 65;
    s = c;
    do
    {
        c = (char) (number % 10) + 47;
        s = s + c;
        number = number / 10;
    } while(number != 0);
    return s;
}*/

/*****************************************************************************/
/* Method that returns the cost in term of components for the multiplication.*/
/*****************************************************************************/

string MultiplicationTree::getCost()
{
    vector<OperationNode*> operation_nodes;
    vector<Node*> nodes;
    vector<string> descriptions;
    vector<int> quantities;
    string s, description;
    int i, j;
    bool found;

    nodes = root->getNodes();
    for(i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->type() == OPERATION)
        {
            operation_nodes.push_back(OperationNode::castToOperationNode(nodes[i]));
        }
    }
    for(i = 0; i < operation_nodes.size(); i++)
    {
        description = operation_nodes[i]->getOperation()->costDescription();
        found = false;
        for (j = 0; j < descriptions.size() && found == false; j++)
        {
            if (descriptions[j].compare(description) == 0)
            {
                found = true;
                quantities[j]++;
            }
        }
        if (found == false)
        {
            descriptions.push_back(description);
            quantities.push_back(1);
        }
    }
    s = "";
    for (i = 0; i < descriptions.size(); i++)
    {
        s = s + to_string(quantities[i]) + " " + descriptions[i];
        if (i + 1 != descriptions.size())
        {
            s = s + ", ";
        }
    }
    return s;
}

long long MultiplicationTree::executeMultiplication(long long input1, long long input2)
{
    long long signX, signY, maskX, maskY, positive, negative, result, test;

    signX = ((input1 >> 63) & 1);
    signY = ((input2 >> 63) & 1);
    maskX = 1;
    maskY = 1;
    maskX <<= lengthX - 1;
    maskY <<= lengthY - 1;
    maskX = maskX - 1;
    maskY = maskY - 1;
    positive = root->executeNode(input1, input2);
    positive |= ((signX & signY) << (lengthX + lengthY - 2));
    negative = ((signX * (input2 & maskY)) << (lengthX - 1));
    negative =  negative + ((signY * (input1 & maskX)) << (lengthY - 1));
    negative = -negative;
    result = positive + negative;
    return result;
}

int MultiplicationTree::getOutputLength()
{
    return (lengthX + lengthY);
}

