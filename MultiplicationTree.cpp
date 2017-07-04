#include "MultiplicationTree.h"
#include "SubMultiplication.h"
#include <stddef.h>
#include <iostream>

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
    Operation operation, *ptr;
    SubMultiplication *subMultiplication;
    int nodeDelay, leftDelay, rightDelay;

    if(next == NULL)
    {
        return 0;
    }
    if(next->isLeaf() == true)
    {
        return 0;
    }
    operationNode = static_cast<OperationNode*>(next);
    nodeDelay = 1;
    if(operationNode->getOperation().OperationID() == 3)
    {
        cout << "Shift" << endl;
        operation = operationNode->getOperation();
        ptr = &operation;
        subMultiplication = dynamic_cast<SubMultiplication*>(ptr);
        nodeDelay = subMultiplication->getMultiplier().getDelay();
    }
    else if (operationNode->getOperation().OperationID() == 0)
    {
        cout << "Shift" << endl;
        nodeDelay = 0;
    }
    leftDelay = delay(operationNode->getLeftChild());
    rightDelay = delay(operationNode->getRightChild());
    if (leftDelay > rightDelay)
        return nodeDelay + leftDelay;
    else
        return nodeDelay + rightDelay;
}