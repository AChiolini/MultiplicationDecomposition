#include <math.h>
#include <iostream>
#include <vector>
#include <memory>
#include "KaratsubaOfman3.h"
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

KaratsubaOfman3::KaratsubaOfman3(vector<Multiplier> multipliers)
{
    this->multipliers = multipliers;
}

/*****************************************************************************/
/* Method that provides all the dispositions available.                      */
/*****************************************************************************/

vector <MultiplicationTree> KaratsubaOfman3::dispositions(short lengthX, short lengthY)
{
    vector <MultiplicationTree> multiplicationTrees;
    MultiplicationTree tmp;
    int i;

    for(i = 0; i < multipliers.size(); i++)
    {
        tmp = dispose (lengthX, lengthY, multipliers[i]);
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

MultiplicationTree KaratsubaOfman3::dispose(short lengthX, short lengthY, Multiplier multiplier)
{
    short lm;
    shared_ptr<InputNode> x2, x1, x0, y2, y1, y0;
    shared_ptr<OperationNode> x2x1, y2y1, x1x0, y1y0, x2x0, y2y0, p22, p11, p00, p21, p10, p20, sp22;
    shared_ptr<OperationNode> first, second, third, first3k, second3k, s3k, first2k, second2k, third2k, s2k, first1k, second1k, s1k, root;
    string s;

    if (lengthX == lengthY && multiplier.getInputLenght1() == multiplier.getInputLenght2() && \
    (((multiplier.getInputLenght1() - 1) * 2) + 1) < lengthX && lengthX <= (((multiplier.getInputLenght1() - 1) * 3) + 1))
    {
        lm = ceil(((double) (lengthX - 1) / 3));
        x0 = make_shared<InputNode>(true, 0, lm);
        x1 = make_shared<InputNode>(true, lm, lm);
        x2 = make_shared<InputNode>(true, 2 * lm, lengthX - 1 - (2 * lm));
        y0 = make_shared<InputNode>(false, 0, lm);
        y1 = make_shared<InputNode>(false, lm, lm);
        y2 = make_shared<InputNode>(false, 2 * lm, lengthX - 1 - (2 * lm));
        x2x1 = make_shared<OperationNode>(make_shared<Subtraction>());
        x2x1->setLeftChild(x2);
        x2x1->setRightChild(x1);
        y2y1 = make_shared<OperationNode>(make_shared<Subtraction>());
        y2y1->setLeftChild(y2);
        y2y1->setRightChild(y1);
        x1x0 = make_shared<OperationNode>(make_shared<Subtraction>());
        x1x0->setLeftChild(x1);
        x1x0->setRightChild(x0);
        y1y0 = make_shared<OperationNode>(make_shared<Subtraction>());
        y1y0->setLeftChild(y1);
        y1y0->setRightChild(y0);
        x2x0 = make_shared<OperationNode>(make_shared<Subtraction>());
        x2x0->setLeftChild(x2);
        x2x0->setRightChild(x0);
        y2y0 = make_shared<OperationNode>(make_shared<Subtraction>());
        y2y0->setLeftChild(y2);
        y2y0->setRightChild(y0);
        p22 = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        p22->setLeftChild(x2);
        p22->setRightChild(y2);
        p11 = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        p11->setLeftChild(x1);
        p11->setRightChild(y1);
        p00 = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        p00->setLeftChild(x0);
        p00->setRightChild(y0);
        p21 = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        p21->setLeftChild(x2x1);
        p21->setRightChild(y2y1);
        p10 = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        p10->setLeftChild(x1x0);
        p10->setRightChild(y1y0);
        p20 = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        p20->setLeftChild(x2x0);
        p20->setRightChild(y2y0);
        sp22 = make_shared<OperationNode>(make_shared<Shift>(4 * lm));
        sp22->setLeftChild(p22);
        first3k = make_shared<OperationNode>(make_shared<Addition>());
        first3k->setLeftChild(p22);
        first3k->setRightChild(p11);
        second3k = make_shared<OperationNode>(make_shared<Subtraction>());
        second3k->setLeftChild(first3k);
        second3k->setRightChild(p21);
        s3k = make_shared<OperationNode>(make_shared<Shift>(3 * lm));
        s3k->setLeftChild(second3k);
        first2k = make_shared<OperationNode>(make_shared<Addition>());
        first2k->setLeftChild(p22);
        first2k->setRightChild(p11);
        second2k = make_shared<OperationNode>(make_shared<Subtraction>());
        second2k->setLeftChild(p00);
        second2k->setRightChild(p20);
        third2k = make_shared<OperationNode>(make_shared<Addition>());
        third2k->setLeftChild(first2k);
        third2k->setRightChild(second2k);
        s2k = make_shared<OperationNode>(make_shared<Shift>(2 * lm));
        s2k->setLeftChild(third2k);       
        first1k = make_shared<OperationNode>(make_shared<Addition>());
        first1k->setLeftChild(p11);
        first1k->setRightChild(p00);
        second1k = make_shared<OperationNode>(make_shared<Subtraction>());
        second1k->setLeftChild(first1k);
        second1k->setRightChild(p10);
        s1k = make_shared<OperationNode>(make_shared<Shift>(lm));
        s1k->setLeftChild(second1k);
        first = make_shared<OperationNode>(make_shared<Addition>());
        first->setLeftChild(sp22);
        first->setRightChild(p00);
        second = make_shared<OperationNode>(make_shared<Addition>());
        second->setLeftChild(s3k);
        second->setRightChild(s1k);
        third = make_shared<OperationNode>(make_shared<Addition>());
        third->setLeftChild(s2k);
        third->setRightChild(second);
        root = make_shared<OperationNode>(make_shared<Addition>());
        root->setLeftChild(third);
        root->setRightChild(first);
        s = "Karatsuba-Ofman three-part splitting (" + to_string(multiplier.getInputLenght1()) + "x" + to_string(multiplier.getInputLenght2()) + ")";
        return MultiplicationTree(root, s);
    }
    return MultiplicationTree();
}
