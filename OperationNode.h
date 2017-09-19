#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H

#include <memory>
#include "Node.h"
#include "Operation.h"

using namespace std;

class OperationNode : public Node
{
    private:
        shared_ptr<Operation> operation;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        
    public:
        OperationNode();
        OperationNode(shared_ptr<Operation>);
        OperationNode(shared_ptr<Operation>, shared_ptr<Node>, shared_ptr<Node>);
        bool isLeaf();
        int getOutputLength();
        shared_ptr<Operation> getOperation();
        shared_ptr<Node> getLeftChild();
        shared_ptr<Node> getRightChild();
        void setOperation(shared_ptr<Operation>);
        void setLeftChild(shared_ptr<Node>);
        void setRightChild(shared_ptr<Node>);
        virtual ~OperationNode() = default;
};

#endif
