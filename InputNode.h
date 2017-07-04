#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "Node.h"

final class InputNode : public Node
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
        void setFirstIndex(bool);
        void setStart(short);
        void setLength(short);
        ~InputNode() = default;
}