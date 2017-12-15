#ifndef INPUTNODE_H
#define INPUTNODE_H

#include <memory>
#include "Node.h"

using namespace std;

/* This class represents an operand of the multiplication. The only information
 * it needs to store are the length and if it is the first or the second operand
 * of the multiplication. Obviously there will be two input node for each 
 * configuration of a multiplication.
 */

class InputNode : public Node
{
    private:
        bool first_input;
        int length;

    public:
        InputNode();
        InputNode(bool, int);
        bool isFirstInput();
        int getLength();
        void setFirstInput(bool);
        void setLength(int);
        NodeType type();
        virtual ~InputNode() = default;

        static InputNode* castToInputNode(Node* node) { return static_cast<InputNode*>(node); }
        static InputNode* castToInputNode(shared_ptr<Node> node) { return static_cast<InputNode*>(node.get()); }
};

#endif
