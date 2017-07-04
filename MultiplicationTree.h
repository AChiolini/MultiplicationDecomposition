#ifndef MULTIPLICATIONTREE_H
#define MULTIPLICATIONTREE_H

class MultiplicationTree
{
	private:
		OperationNode* root;

    public:
        MultiplicationTree();
        MultiplicationTree(OperationNode*)
        OperationNode* getRoot();
        void setRoot(OperationNode*)
        int getDelay();
        virtual ~MultiplicationTree() = default;
};

#endif
