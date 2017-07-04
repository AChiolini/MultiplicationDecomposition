#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H

#include "Node.h"

final class OperationNode : public Node
{
    private:
        Operation operation;
        int shift;
        Node *left;
        Node *right;
        
    public:
        OperationNode();
        OperationNode(Operation);
        bool isLeaf();
        Operation getOperation();
        Node* getLeftChild();
        Node* getRightChild();
        int getShift();
        void setOperation(Operation)
        void setLeftChild(Node*);
        void setRightChild(Node*);
        void setShift();
        ~OperationNode();
};

#endif