#ifndef MULTIPLICATIONTREE_H
#define MULTIPLICATIONTREE_H

#include <string>
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

    public:
        MultiplicationTree();
        MultiplicationTree(shared_ptr<OperationNode>, string);
        shared_ptr<OperationNode> getRoot();
        string getDescription();
        int getDelay();
        string getExpression();
        void setRoot(shared_ptr<OperationNode>);
	void setDescription(string);	
        virtual ~MultiplicationTree() = default;
};

#endif
