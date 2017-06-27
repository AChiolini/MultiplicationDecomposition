#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H

#include "Node.h"

final class OperationNode : public Node
{
    private:
        //Operazione
        Node *left;
        Node *right;
        
    public:
        OperationNode();
        bool isLeaf();
        // getOperation();
        Node* getLeftChild();
        Node* getRightChild();
        //setOperation()
        void setLeftChild(Node*);
        void setRightChild(Node*);
        ~OperationNode();
};

#endif