#include "MultiplicationTree.h"
#include <stddef.h>

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
    return 0;
}

void setRoot(OperationNode *root)
{
    this->root = root;
}