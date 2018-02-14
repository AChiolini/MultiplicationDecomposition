#ifndef MULTIPLICATIONTREE_H
#define MULTIPLICATIONTREE_H

#include <string>
#include <vector>
#include "../Node/OperationNode.h"

using namespace std;

/*****************************************************************************/
/* Class that contains the tree of the multiplication and provides several   */
/* methods that provides information about the tree.                         */
/*****************************************************************************/

class MultiplicationTree
{
    private:
        int length_x;
        int length_y;
	    shared_ptr<OperationNode> root;
        string description;
        vector<Variable> assignment(vector<Node*>);
        string getVariableName(int);

    public:
        MultiplicationTree();
        MultiplicationTree(const MultiplicationTree&) = default;
        MultiplicationTree(shared_ptr<OperationNode>, string, int, int);
        shared_ptr<OperationNode> getRoot();
        string getDescription();
        int getLatency();
        string getExpression();
        string getCost();
        int getLengthX();
        int getLengthY();
        int getOutputLength();
        string getAllInfo(long long, long long);
        void setRoot(shared_ptr<OperationNode>);
        void setDescription(string);
        void setLengthX(int);
        void setLengthY(int);
        MultiplicationTree copyTree();
        long long executeMultiplication(long long, long long);
        virtual ~MultiplicationTree() = default;
};

#endif
