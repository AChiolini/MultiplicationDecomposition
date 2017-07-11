#ifndef MULTIPLICATIONTREE_H
#define MULTIPLICATIONTREE_H

#include "OperationNode.h"

class MultiplicationTree
{
    private:
	    OperationNode* root;
        int delay(Node*);
        void balanceSubTree(Node*);

    public:
        MultiplicationTree();
        MultiplicationTree(OperationNode*);
        OperationNode* getRoot();
        void setRoot(OperationNode*);
        int getDelay();
	void optimize();
        virtual ~MultiplicationTree() = default;
};

#endif
