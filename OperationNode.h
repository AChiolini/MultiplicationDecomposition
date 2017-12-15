#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H

#include <memory>
#include "Node.h"
#include "Operation.h"
#include "Link.h"

using namespace std;

/* This class represents an operation. It could be an addition, a subtraction or
 * a (sub)multiplication. 
 * The class also requires the two operand of the operation.
 * If length is set to -1 it means that the length of the output depends by the
 * the operation and the operands. However, in some case it's possible to ignore
 * some bits because the would not be used for some reason.
 */

class OperationNode : public Node
{
    private:
        shared_ptr<Operation> operation;
        Link first_operand;
        Link second_operand;
        int length;
        
    public:
        OperationNode();
        OperationNode(shared_ptr<Operation>);
        OperationNode(shared_ptr<Operation>, Link, Link);
        OperationNode(shared_ptr<Operation>, Link, Link, int);
        shared_ptr<Operation> getOperation();
        Link getFirstOperand();
        Link getSecondOperand();
        int getLength();
        void setOperation(shared_ptr<Operation>);
        void setFirstOperand(Link);
        void setSecondOperand(Link);
        void setLength(int);
        NodeType type();
        virtual ~OperationNode() = default;

        static OperationNode* castToOperationNode(Node* node) { return static_cast<OperationNode*>(node); }
        static OperationNode* castToOperationNode(shared_ptr<Node> node) { return static_cast<OperationNode*>(node.get()); }
};

#endif
