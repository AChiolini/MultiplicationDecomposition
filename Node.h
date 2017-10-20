#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

enum Sign
{
    POSITIVE = 0,
    NEGATIVE,
    UNDEFINED
};

typedef struct OutputSpecifications 
{
    Sign sign;
    int MCS;
    int length;
} OutSpecs;

class Node
{
    public:
        virtual bool isLeaf() = 0;
        virtual int getOutputLength() = 0;
        virtual OutSpecs getOutputSpecifications() = 0; 
        virtual ~Node() = default;
};

#endif
