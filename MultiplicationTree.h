#ifndef MULTIPLICATIONTREE_H
#define MULTIPLICATIONTREE_H

#include <string>
#include <vector>
#include "OperationNode.h"
#include "InputNode.h"

using namespace std;

/*****************************************************************************/
/* Class that contains the tree of the multiplication and provides several   */
/* methods that provides information about the tree.                         */
/*****************************************************************************/

class MultiplicationTree
{
    private:
	shared_ptr<OperationNode> root;
        string description;
        int delay(shared_ptr<Node>);
        string expression(shared_ptr<Node>);
        vector<OperationNode*> cost(shared_ptr<Node>);
        long long execute(shared_ptr<Node>, long long, long long);

    public:
        MultiplicationTree();
        MultiplicationTree(shared_ptr<OperationNode>, string);
        shared_ptr<OperationNode> getRoot();
        string getDescription();
        int getDelay();
        string getExpression();
        string getCost();
        void setRoot(shared_ptr<OperationNode>);
	void setDescription(string);	
        long long executeMultiplication(long long, long long);
        virtual ~MultiplicationTree() = default;
};

#endif
