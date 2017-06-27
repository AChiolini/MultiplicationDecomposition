#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "Node.h"

final class InputNode : public Node
{
    private:
        short xIndex;
        short yIndex;

    public:
        InputNode();
        InputNode(short, short);
        bool isLeaf();
        short getXIndex();
        short getYIndex();
        void setXIndex();
        void setYIndex();
        ~InputNode() = default;
}