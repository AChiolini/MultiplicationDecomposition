#ifndef MULTIPLICATIONTREE_H
#define MULTIPLICATIONTREE_H

#include <string>
#include "OperationNode.h"
#include "InputNode.h"

class MultiplicationTree
{
    private:
	OperationNode* root;
        int delay(Node*);
        std::string expression(Node*);

    public:
        MultiplicationTree();
        MultiplicationTree(OperationNode*);
        OperationNode* getRoot();
        void setRoot(OperationNode*);
        int getDelay();
	char* getExpression();
        virtual ~MultiplicationTree() = default;
};

#endif
