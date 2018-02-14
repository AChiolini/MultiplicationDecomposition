#include <stddef.h>
#include <iostream>
#include <string.h>
#include "MultiplicationTree.h"
#include "../Node/InputNode.h"
#include "../Operation/Addition.h"
#include "../Operation/Multiplication.h"
#include "../Operation/And.h"
#include "../Operation/C2.h"
#include "../Operation/Shift.h"
#include "../Operation/Fanout.h"

using namespace std;

/*****************************************************************************/
/* Default constructor which set the tree to NULL.                           */
/*****************************************************************************/

MultiplicationTree::MultiplicationTree()
{
    this->root = nullptr;
    this->description = "";
    this->length_x = 0;
    this->length_y = 0;
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

MultiplicationTree MultiplicationTree::copyTree()
{
    int i, j, k,root_position;
    vector<Node*> nodes;
    vector<shared_ptr<Node>> copy_nodes;
    Link link;
    OperationNode *operation_node;
    shared_ptr<Operation> operation, copied_operation;
    shared_ptr<OperationNode> copied_operation_node, root;

    if(this->root == nullptr)
    {
        return MultiplicationTree();
    }
    // Copying all the nodes
    nodes = this->root->getNodes();
    // Finding root
    for(i = 0; i < nodes.size(); i++)
    {
        if(this->root.get() == nodes[i])
        {
            root_position = i;
        }
    }
    for(i = 0; i < nodes.size(); i++)
    {
        switch(nodes[i]->type())
        {
            case INPUT: copy_nodes.push_back(make_shared<InputNode>(*(InputNode::castToInputNode(nodes[i]))));
                break;
            case OPERATION: operation_node = OperationNode::castToOperationNode(nodes[i]);
                operation = operation_node->getOperation();
                switch(operation->type())
                {
                    case ADDITION: copied_operation = make_shared<Addition>(*(Addition::castToAddition(operation)));
                        break;
                    case MULTIPLICATION: copied_operation = make_shared<Multiplication>(*(Multiplication::castToMultiplication(operation)));
                        break;
                    case AND: copied_operation = make_shared<And>(*(And::castToAnd(operation)));
                        break;
                    case SHIFT: copied_operation = make_shared<Shift>(*(Shift::castToShift(operation)));
                        break;
                    case COMPLEMENT2: copied_operation = make_shared<C2>(*(C2::castToC2(operation)));
                        break;
                    case FANOUT: copied_operation = make_shared<Fanout>(*(Fanout::castToFanout(operation)));
                        break;
                }
                copied_operation_node = make_shared<OperationNode>(copied_operation, operation_node->getLength());
                if(i == root_position)
                {
                    root = copied_operation_node;
                }
                copy_nodes.push_back(copied_operation_node);
                break;
        }
    }
    // Setting links
    for(i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->type() == OPERATION)
        {
            operation_node = OperationNode::castToOperationNode(nodes[i]);
            for(j = 0; j < operation_node->size(); j++)
            {
                link = operation_node->getOperandAt(j);
                for(k = 0; k < nodes.size(); k++)
                {
                    if(link.getNode().get() == nodes[k])
                    {
                        link.setNode(copy_nodes[k]);
                    }
                }
                OperationNode::castToOperationNode(copy_nodes[i])->insertOperandLast(link);
            }
        }
    }
    return MultiplicationTree(root, this->description, this->length_x, this->length_y);
}

long long MultiplicationTree::executeMultiplication(long long input1, long long input2)
{
    return root->executeNode(input1, input2);
}

int MultiplicationTree::getOutputLength()
{
    return (length_x + length_y);
}

