#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "Node.h"

class InputNode : public Node
{
    private:
        bool firstInput;
        short start;
        short length;

    public:
        InputNode();
        InputNode(bool, short, short);
        bool isLeaf();
        bool isFirstInput();
        short getStart();
        short getLength();
        void setFirstInput(bool);
        void setStart(short);
        void setLength(short);
        virtual ~InputNode() = default;
};

#endif
