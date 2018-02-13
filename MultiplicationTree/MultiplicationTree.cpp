#include <stddef.h>
#include <iostream>
#include <string.h>
#include "MultiplicationTree.h"
#include "../Node/InputNode.h"

using namespace std;

/*****************************************************************************/
/* Default constructor which set the tree to NULL.                           */
/*****************************************************************************/

MultiplicationTree::MultiplicationTree()
{
    cout << "empty construct called" << endl;
    this->root = nullptr;
    this->description = "";
    this->length_x = 0;
    this->length_y = 0;
    cout << "empty construct terminated" << endl;
}

MultiplicationTree::MultiplicationTree(const MultiplicationTree &multiplication_tree)
{
    cout << "am i called?" << endl;
    this->length_x = multiplication_tree.length_x;
    this->length_y = multiplication_tree.length_y;
    this->root = make_shared<OperationNode>(*(multiplication_tree.root.get()));
    this->description = multiplication_tree.description;
}

/*****************************************************************************/
/* Constructor that required the root operation node of the tree and a       */
/* description.                                                              */
/*****************************************************************************/

MultiplicationTree::MultiplicationTree(shared_ptr<OperationNode> root, string description, int length_x, int length_y)
{
    this->root = root;
    this->description = description;
    this->length_x = length_x;
    this->length_y = length_y;
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
    return length_x;
}

int MultiplicationTree::getLengthY()
{
    return length_y;
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

void MultiplicationTree::setLengthX(int length_x)
{

    this->length_x = length_x;
}

void MultiplicationTree::setLengthY(int length_y)
{
    this->length_y = length_y;
}

/*****************************************************************************/
/* Method that returns the string of the mathematical expression of the tree.*/
/*****************************************************************************/

string MultiplicationTree::getExpression()
{
    vector<Node*> nodes;
    vector<InputNode*> inputs;
    vector<OperationNode*> operations;
    vector<Variable> variables;
    Variable var;
    string expression, s;
    int i;

    expression = "\n";
    nodes = this->root->getNodes();
    for(i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->type() == OPERATION)
        {
            operations.push_back(OperationNode::castToOperationNode(nodes[i]));
        }
        else
        {
            inputs.push_back(InputNode::castToInputNode(nodes[i]));
        }
    }
    for(i = 0; i < inputs.size(); i ++)
    {
        s = inputs[i]->getVariableName();
        var.name = s;
        var.ptr = inputs[i];
        variables.push_back(var);
        expression = expression + s + " = Input\n";
    }
    for(i = 0; i < operations.size(); i ++)
    {
        var.name = this->getVariableName(i);
        var.ptr = operations[i];
        variables.push_back(var);
    }
    for(i = 0; i < operations.size(); i ++)
    {
        if(operations.size() - 1 != i)
        {
            expression = expression + operations[i]->getOperationExpression(variables) + "\n";
        }
        else
        {
            expression = expression + operations[i]->getOperationExpression(variables);
        }
    }
    return expression;
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
        c = (char) (number % 10) + 48;
        s = s + c;
        number = number / 10;
    } while(number != 0);
    return s;
}

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
    return root->executeNode(input1, input2);
}

int MultiplicationTree::getOutputLength()
{
    return (length_x + length_y);
}

