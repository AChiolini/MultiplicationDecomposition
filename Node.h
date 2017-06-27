#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

class Node
{
    public:
        virtual bool isLeaf() = 0;
        virtual ~Node() = default;
};

#endif