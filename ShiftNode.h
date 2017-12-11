#ifndef SHIFTNODE_H
#define SHIFTNODE_H

#include "Node.h"
#include "Link.h"

using namespace std;

/* This class represents a shift operation. The information it need to store are:
 * operand: the link to the operand it needs to shift.
 * shift: the shift value.
 */

class ShiftNode : public Node
{
    private:
        Link operand;
        int shift;

    public:
        ShiftNode();
        ShiftNode(Link);
        ShiftNode(Link, int);
        Link getOperand();
        int getShift();
        void setOperand(Link);
        void setShift(int);
        NodeType type();
        int getLength();
        virtual ~ShiftNode() = default;

        static ShiftNode* castToShiftNode(Node* node) { return static_cast<ShiftNode*>(node); }
        static ShiftNode* castToShiftNode(shared_ptr<Node> node) { return static_cast<ShiftNode*>(node.get()); }
};

#endif
