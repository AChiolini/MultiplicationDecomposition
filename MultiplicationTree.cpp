#include <stddef.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include "MultiplicationTree.h"
#include "SubMultiplication.h"
#include "ShiftNode.h"
#include "InputNode.h"

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

int MultiplicationTree::getDelay()
{
    return delay(root);
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
/* Recursive method that calculates the delay of the tree.                   */
/*****************************************************************************/

int MultiplicationTree::delay(shared_ptr<Node> next)
{
    OperationNode *operation_node;
    ShiftNode *shift_node;
    SubMultiplication *sub_multiplication;
    int node_delay, first_operand_delay, second_operand_delay, total_delay;

    if(next == nullptr)
    {
        return 0;
    }
    if(next->type() == INPUT)
    {
        total_delay = 0;
    }
    else if(next->type() == OPERATION)
    {
        operation_node = OperationNode::castToOperationNode(next);
        if(operation_node->getOperation()->type() == SUBMULTIPLICATION)
        {
            sub_multiplication = static_cast<SubMultiplication*>(operation_node->getOperation().get()); //Mettere funzione statica per cast
            node_delay = sub_multiplication->getMultiplier().getDelay();
        }
        else
        {
            node_delay = 1;
        }
        first_operand_delay = delay(operation_node->getFirstOperand().getNode());
        second_operand_delay = delay(operation_node->getSecondOperand().getNode());
        if(first_operand_delay > second_operand_delay)
        {
            total_delay = node_delay + first_operand_delay;
        }
        else
        {
            total_delay = node_delay + second_operand_delay;
        }
    }
    else
    {
        shift_node = ShiftNode::castToShiftNode(next);
        node_delay = 0;
        first_operand_delay = delay(shift_node->getOperand().getNode());
        total_delay = node_delay + first_operand_delay;
    }
    return total_delay;
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
        switch(operations[i]->getOperation()->type())
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
                    singleDescription = singleDescription + "Multiplier (" + to_string(multiplier.getInputLength1()) + "x";
                    singleDescription = singleDescription + to_string(multiplier.getInputLength2()) + ")";
                }
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
    vector<OperationNode*> operations, child_operations;
    OperationNode *operation_node;
    int i;

    if (next == nullptr)
    {
        return operations;
    }
    if (next->type() == OPERATION)
    {
        operation_node = OperationNode::castToOperationNode(next);
        operations.push_back(operation_node);
        child_operations = cost(operation_node->getFirstOperand().getNode());
        for (i = 0; i < child_operations.size(); i++)
        {
            if(find(operations.begin(), operations.end(), child_operations[i]) == operations.end())
            {
                operations.push_back(child_operations[i]);
            }
        }
        child_operations = cost(operation_node->getSecondOperand().getNode());
        for (i = 0; i < child_operations.size(); i++)
        {
            if(find(operations.begin(), operations.end(), child_operations[i]) == operations.end())
            {
                operations.push_back(child_operations[i]);
            }
        }
    }
    return operations;
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
    positive = execute(root, input1, input2);
    positive |= ((signX & signY) << (lengthX + lengthY - 2));
    negative = ((signX * (input2 & maskY)) << (lengthX - 1));
    negative =  negative + ((signY * (input1 & maskX)) << (lengthY - 1));
    negative = -negative;
    result = positive + negative;
    return result;
}

long long MultiplicationTree::execute(shared_ptr<Node> next, long long input1, long long input2)
{
    OperationNode *operation_node;
    InputNode *input_node;
    ShiftNode *shift_node;
    long long value, first_operand, second_operand, and_mask, sign_extension;

    if(next == nullptr)
    {
        return 0;
    }
    if(next->type() == INPUT)
    {
        input_node = InputNode::castToInputNode(next);
        if(input_node->isFirstInput() == true)
        {
            value = input1;
	}
        else
        {
            value = input2;
        }
        and_mask = 1;
        and_mask <<= (input_node->getLength());
        and_mask--;
        value &= and_mask;
    }
    else if(next->type() == SHIFT)
    {
        shift_node = ShiftNode::castToShiftNode(next);
        value = execute(shift_node->getOperand().getNode(), input1, input2);
        value <<= shift_node->getShift();
    }
    else
    {
        operation_node = OperationNode::castToOperationNode(next);
        first_operand = execute(operation_node->getFirstOperand().getNode(), input1, input2);
        and_mask = 1;
        and_mask <<= (operation_node->getFirstOperand().getLength());
        and_mask--;
        first_operand >>= (operation_node->getFirstOperand().getStart());
        first_operand &= and_mask;
        //Sign extension. Not needed in hardware.
        sign_extension = -1;
        sign_extension ^= and_mask;
        and_mask = 1;
        and_mask <<= (operation_node->getFirstOperand().getLength() - 1);
        if(and_mask & first_operand)
        {
            first_operand += sign_extension;
        }
        //End of sign extension.
        second_operand = execute(operation_node->getSecondOperand().getNode(), input1, input2);
        and_mask = 1;
        and_mask <<= (operation_node->getSecondOperand().getLength());
        and_mask--;
        second_operand >>= (operation_node->getSecondOperand().getStart());
        second_operand &= and_mask;
        //Sign extension. Not needed in hardware.
        sign_extension = -1;
        sign_extension ^= and_mask;
        and_mask = 1;
        and_mask <<= (operation_node->getSecondOperand().getLength() - 1);
        if(and_mask & second_operand)
        {
            second_operand += sign_extension;
        }
        //End of sign extension.
        switch (operation_node->getOperation()->type())
        {
            case ADDITION: value = first_operand + second_operand;
                break;
            case SUBTRACTION: value = first_operand - second_operand;
                break;
            case SUBMULTIPLICATION: value = first_operand * second_operand;
                break;
        }
    }
    return value;
}

int MultiplicationTree::getOutputLength()
{
    return (lengthX + lengthY);
}
