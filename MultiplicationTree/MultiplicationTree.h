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

typedef struct
{
    Node *ptr;
    string name;
} Variable;

class MultiplicationTree
{
    private:
        int lengthX;
        int lengthY;
	    shared_ptr<OperationNode> root;
        string description;
        string expression(shared_ptr<Node>);
        //vector<Variable> assignment(shared_ptr<Node>);
        //string getVariableName(int);

    public:
        MultiplicationTree();
        MultiplicationTree(shared_ptr<OperationNode>, string, int, int);
        shared_ptr<OperationNode> getRoot();
        string getDescription();
        int getLatency();
        string getExpression();
        string getCost();
        int getLengthX();
        int getLengthY();
        int getOutputLength();
        void setRoot(shared_ptr<OperationNode>);
        void setDescription(string);
        void setLengthX(int);
        void setLengthY(int);
        long long executeMultiplication(long long, long long);
        virtual ~MultiplicationTree() = default;
};

#endif
