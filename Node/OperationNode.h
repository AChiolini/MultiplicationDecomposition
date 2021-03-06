#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H

#include <memory>
#include <vector>
#include "Node.h"
#include "../Operation/Operation.h"
#include "../Link/Link.h"

using namespace std;

/* This class represents an operation with 1 operand. It could be a shift or
 * a two's complement. 
 * The class requires just one operand and the operation.
 * If length is set to -1 it means that the length of the output depends by the
 * the operation and the operands. However, in some case it's possible to ignore
 * some bits because the would not be used for some reason.
 */

typedef struct
{
    Node *ptr;
    string name;
} Variable;

class OperationNode : public Node
{
    private:
        // Class attributes
        shared_ptr<Operation> operation;
        vector<Link> operands;
        int length;
        // Class methods
        void checkValidity();
        
    public:
        // Class constructors
        OperationNode();
        OperationNode(const OperationNode&) = default;
        OperationNode(shared_ptr<Operation>);
        OperationNode(shared_ptr<Operation>, int);
        // Class methods
        shared_ptr<Operation> getOperation();
        int getLength();
        void setOperation(shared_ptr<Operation>);
        void setLength(int);
        void insertOperandFirst(Link);
        void insertOperandLast(Link);
        void removeOperandAt(int);
        void clearOperands();
        int size();
        Link getOperandAt(int);
        string getOperationExpression(vector<Variable>);
        // Inherited methods
        NodeType type() const;
        double getLatency();
        vector<Node*> getNodes();
        void substituteLeaves(shared_ptr<Node>, shared_ptr<Node>);
        vector<OperationNode*> shiftLinksOperands(int, int, vector<OperationNode*>);
        long long executeNode(long long, long long);
        // Class destructor
        virtual ~OperationNode() = default;
        // Static methods
        static OperationNode* castToOperationNode(Node* node) { return static_cast<OperationNode*>(node); }
        static OperationNode* castToOperationNode(shared_ptr<Node> node) { return static_cast<OperationNode*>(node.get()); }
};

#endif
