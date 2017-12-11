#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

/*enum Sign
{
    POSITIVE = 0,
    UNDEFINED
};*/

enum NodeType
{
    INPUT = 0,
    OPERATION,
    SHIFT
};

/*typedef struct OutputSpecifications 
{
    Sign sign;
    int MCS;
    int length;
} OutSpecs;*/

class Node
{
    public:
        virtual NodeType type() = 0;
        virtual int getLength() = 0;
        virtual ~Node() = default;
};

#endif
