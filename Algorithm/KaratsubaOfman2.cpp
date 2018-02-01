#include <math.h>
#include <iostream>
#include <vector>
#include <memory>
#include "KaratsubaOfman2.h"
#include "StandardTiling.h"
#include "ProposedTiling.h"
#include "MultiplicationTree.h"
#include "SubMultiplication.h"
#include "InputNode.h"
#include "OperationNode.h"
#include "Subtraction.h"
#include "Addition.h"
#include "Shift.h"

using namespace std;


/*****************************************************************************/
/* Constructor that accepts the multipliers available.                       */
/*****************************************************************************/

KaratsubaOfman2::KaratsubaOfman2(vector<Multiplier> multipliers)
{
    this->multipliers = multipliers;
}

/*****************************************************************************/
/* Method that provides all the dispositions available.                      */
/*****************************************************************************/

vector <MultiplicationTree> KaratsubaOfman2::dispositions(int x, int y)
{








    /*vector <MultiplicationTree> multiplicationTrees;
    shared_ptr<Multiplication> algorithm;
    vector <Multiplier> mult;
    MultiplicationTree tmp;
    int i, j;

    for (i = 0; i < multipliers.size(); i++)
    {
        mult.push_back(multipliers[i]);
        for (j = 0; j < 2; j++)
        {
            switch (j)
            {
                case 0: algorithm = make_shared<StandardTiling>(mult);
                        break;
                case 1: algorithm = make_shared<ProposedTiling>(mult);
                        break;
            }
            tmp = dispose (lengthX, lengthY, algorithm.get(), multipliers[i]);
            if(tmp.getRoot() != nullptr)
            {
                multiplicationTrees.push_back(tmp);
            }
        }
        mult.clear();
    }
    return multiplicationTrees;*/
}

/*****************************************************************************/
/* Method that tries to create a disposition given two input lengths and a   */
/* multiplier.                                                               */
/*****************************************************************************/

vector<MultiplicationTree> KaratsubaOfman2::dispose(int x, int y, Multiplier multiplier)
{
    vector<MultiplicationTree> dispositions;
    // First of all, pre checks
    // Both lengths must be greater than 1, otherwise there aren't enough bit for the multiplication.
    if(x <= 1 || y <= 1)
    {
        dispositions.push_back(MultiplicationTree());
        return dispositions;
    }
    // Checking if the multiplication can be mapped in one LUT
    if(Algorithm::isLUTMapped(x, y, multiplier) == true)
    {
        dispositions.push_back(MultiplicationTree());
        return dispositions;
    }
    else
    {
        //Checking if can be done with just a multiplier
        if((multiplier.getInputLength1() >= x && multiplier.getInputLength2() >= y) ||\
           (multiplier.getInputLength1() >= y && multiplier.getInputLength2() >= x))
        {
            dispositions.push_back(MultiplicationTree());
            return dispositions;
        }
    }
    // Checking if it can be splitted in two parts in which each part is covered just by a multiplier
    // If it is, then call not_recursive disposition, otherwise call recursive_disposition
    if(((multiplier.getInputLength1() * 2) - 1 <= x && (multiplier.getInputLength2() * 2) - 1 <= y) ||\
       ((multiplier.getInputLength2() * 2) - 1 <= x && (multiplier.getInputLength1() * 2) - 1 <= y))
    {

    }
    else
    {

    }









    /*short lm;
    vector<MultiplicationTree> m0, m1, m2;
    vector<shared_ptr<Node>> leaves, leaves2;
    InputNode *tmp;
    shared_ptr<InputNode> x1, x0, y1, y0;
    shared_ptr<OperationNode> dX, dY, dXdY, x0y0, x1y1, halfMiddle, pMiddle, middle, first, last, root;
    string s;
    int i;

    if (lengthX == lengthY)
    {
        // If both lengthX and lengthY are less than the lenghts of the multiplier i don't have to compute the Karatsuba-Ofman
        if (lengthX > multiplier.getInputLength1() || lengthX > multiplier.getInputLength2())
        {
            lm = lengthX/2;
            // Computing the direct products
            m0 = algorithm->dispositions(lm + 1, lm + 1);
            m1 = algorithm->dispositions(lengthX - lm, lengthX - lm);
            m2 = algorithm->dispositions(lm + 1, lm + 1);
            if (m1.size() == 1 && m0.size() == 1 && m2.size() == 1)
            {
                x0y0 = m0[0].getRoot();
                x1y1 = m1[0].getRoot();
                dXdY = m2[0].getRoot();
                // I have to shift all the x1y1 inputs of lm
                leaves = x1y1->getLeaves();
                for (i = 0; i < leaves.size(); i++)
                {
                    tmp = InputNode::castToInputNode(leaves[i]);
                    tmp->setStart(tmp->getStart() + lm);
                }
                leaves2 = x0y0->getLeaves();
                for (i = 0; i < leaves2.size(); i++)
                {
                    leaves.push_back(leaves2[i]);
                }
                // Substitute all the input nodes of dxdy with subtractions
                substituteLeaves(dXdY, leaves, lm);     
                halfMiddle = make_shared<OperationNode>(make_shared<Addition>());
                halfMiddle->setLeftChild(x1y1);
                halfMiddle->setRightChild(x0y0);
                pMiddle = make_shared<OperationNode>(make_shared<Subtraction>());
                pMiddle->setLeftChild(halfMiddle);
                pMiddle->setRightChild(dXdY);        
                middle = make_shared<OperationNode>(make_shared<Shift>(lm));
                middle->setLeftChild(pMiddle);
                first = make_shared<OperationNode>(make_shared<Shift>(2 * lm));
                first->setLeftChild(x1y1);
                last = make_shared<OperationNode>(make_shared<Addition>());
                last->setLeftChild(first);
                last->setRightChild(x0y0);
                root = make_shared<OperationNode>(make_shared<Addition>());
                root->setLeftChild(middle);
                root->setRightChild(last);
                s = "Karatsuba-Ofman 2 way split";
                return MultiplicationTree(root, s, (int) lengthX, (int) lengthY);
            }
        }
    }
    return MultiplicationTree();*/
}

void KaratsubaOfman2::substituteLeaves(shared_ptr<Node> next, vector<shared_ptr<Node>> inputNodes, int lm)
{
    OperationNode* operationNode;
    InputNode *inputNode, *tmp;
    shared_ptr<OperationNode> sub1, sub2;
    shared_ptr<Node> d3, d2, d1, d0;
    int i;
    bool found;

    if (next->isLeaf() == false)
    {
        operationNode = OperationNode::castToOperationNode(next);
        if (operationNode->getOperation()->getOperationType() == SUBMULTIPLICATION)
        {
            inputNode = InputNode::castToInputNode(operationNode->getLeftChild());
            sub1 = make_shared<OperationNode>(make_shared<Subtraction>());
            found = false;
            for (i = 0; i < inputNodes.size() && found == false; i++)
            {
                tmp = InputNode::castToInputNode(inputNodes[i]);
                if ((inputNode->isFirstInput() == tmp->isFirstInput()) && \
                    (inputNode->getStart() + lm == tmp->getStart()) && \
                    (inputNode->getLength() == tmp->getLength()))
                {
                    found = true;
                    d1 = inputNodes[i];
                }
            }
            sub1->setLeftChild(d1);
            found = false;
            for (i = 0; i < inputNodes.size() && found == false; i++)
            {
                tmp = InputNode::castToInputNode(inputNodes[i]);
                if ((inputNode->isFirstInput() == tmp->isFirstInput()) && \
                    (inputNode->getStart() == tmp->getStart()) && \
                    (inputNode->getLength() == tmp->getLength()))
                {
                    found = true;
                    d0 = inputNodes[i];
                }
            }
            sub1->setRightChild(d0);
            inputNode = InputNode::castToInputNode(operationNode->getRightChild());
            sub2 = make_shared<OperationNode>(make_shared<Subtraction>());
            found = false;
            for (i = 0; i < inputNodes.size() && found == false; i++)
            {
                tmp = InputNode::castToInputNode(inputNodes[i]);
                if ((inputNode->isFirstInput() == tmp->isFirstInput()) && \
                    (inputNode->getStart() + lm == tmp->getStart()) && \
                    (inputNode->getLength() == tmp->getLength()))
                {
                    found = true;
                    d3 = inputNodes[i];
                }
            }
            sub2->setLeftChild(d3);
            found = false;
            for (i = 0; i < inputNodes.size() && found == false; i++)
            {
                tmp = InputNode::castToInputNode(inputNodes[i]);
                if ((inputNode->isFirstInput() == tmp->isFirstInput()) && \
                    (inputNode->getStart() == tmp->getStart()) && \
                    (inputNode->getLength() == tmp->getLength()))
                {
                    found = true;
                    d2 = inputNodes[i];
                }
            }
            sub2->setRightChild(d2);
	    operationNode->setLeftChild(sub1);
            operationNode->setRightChild(sub2);
        }
        else
        {
              substituteLeaves(operationNode->getLeftChild(), inputNodes, lm);
              substituteLeaves(operationNode->getRightChild(), inputNodes, lm);
        }
    }
}
