#include <math.h>
#include <iostream>
#include <vector>
#include <memory>
#include "KaratsubaOfman.h"
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

KaratsubaOfman::KaratsubaOfman(Multiplier *multipliers, int nMultipliers)
{
    this->multipliers = multipliers;
    this->nMultipliers = nMultipliers;
}

/*****************************************************************************/
/* Method that provides all the dispositions available.                      */
/*****************************************************************************/

vector <MultiplicationTree> KaratsubaOfman::dispositions(short lengthX, short lengthY)
{
    vector <MultiplicationTree> multiplicationTrees;
    MultiplicationTree tmp;
    int i;

    for(i = 0; i < nMultipliers; i++)
    {
        tmp = dispose (lengthX, lengthY, i);
        if(tmp.getRoot() != nullptr)
        {
            multiplicationTrees.push_back(tmp);
        }
    }
    return multiplicationTrees;
}

/*****************************************************************************/
/* Method that tries to create a disposition given two input lenghts and a   */
/* multiplier.                                                               */
/*****************************************************************************/

MultiplicationTree KaratsubaOfman::dispose(short lengthX, short lengthY, int index)
{
    short lm;
    shared_ptr<InputNode> x1, x0, y1, y0;
    shared_ptr<OperationNode> dX, dY, dXdY, x0y0, x1y1, halfMiddle, pMiddle, middle, first, last, root;
    string s;

    if (lengthX == lengthY && multipliers[index].getInputLenght1() == multipliers[index].getInputLenght2() && \
    (multipliers[index].getInputLenght1() * 2) > lengthX && lengthX > multipliers[index].getInputLenght1())
    {
        lm = lengthX/2;
        x0 = make_shared<InputNode>(true, 0, lm);
        x1 = make_shared<InputNode>(true, lm, lengthX - lm - 1);
        y0 = make_shared<InputNode>(false, 0, lm);
        y1 = make_shared<InputNode>(false, lm, lengthY - lm - 1);
        dX = make_shared<OperationNode>(make_shared<Subtraction>());
        dX->setLeftChild(x1);
        dX->setRightChild(x0);
        dY = make_shared<OperationNode>(make_shared<Subtraction>());
        dY->setLeftChild(y1);
        dY->setRightChild(y0);
        dXdY = make_shared<OperationNode>(make_shared<SubMultiplication>(multipliers[index]));
        dXdY->setLeftChild(dX);
        dXdY->setRightChild(dY);        
        x1y1 = make_shared<OperationNode>(make_shared<SubMultiplication>(multipliers[index]));
        x1y1->setLeftChild(x1);
        x1y1->setRightChild(y1);
        x0y0 = make_shared<OperationNode>(make_shared<SubMultiplication>(multipliers[index]));
        x0y0->setLeftChild(x0);
        x0y0->setRightChild(y0);
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
        s = "Karatsuba-Ofman 2 way split (" + to_string(multipliers[index].getInputLenght1()) + "x" + to_string(multipliers[index].getInputLenght2()) + ")";
        return MultiplicationTree(root, s);
    }
    return MultiplicationTree();
}
