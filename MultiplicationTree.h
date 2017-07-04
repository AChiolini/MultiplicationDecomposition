#ifndef MULTIPLICATIONTREE_H
#define MULTIPLICATIONTREE_H

#include "OperationNode.h"

class MultiplicationTree
{
	private:
		OperationNode* root;
        int delay(Node*);

    public:
        MultiplicationTree();
        MultiplicationTree(OperationNode*);
        OperationNode* getRoot();
        void setRoot(OperationNode*);
        int getDelay();
        virtual ~MultiplicationTree() = default;
};

#endif
