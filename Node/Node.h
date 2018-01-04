#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <vector>

using namespace std;

enum NodeType
{
    INPUT = 0,
    OPERATION,
};

class Node
{
    public:
        virtual NodeType type() = 0;
        virtual int getLength() = 0;
        virtual double getLatency() = 0;
        virtual vector<Node*> getNodes() = 0;
        virtual long long executeNode(long long, long long) = 0;
        virtual ~Node() = default;
};

#endif
