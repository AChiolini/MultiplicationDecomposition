#include "KaratsubaOfman.h"
#include "MultiplicationTree.h"
#include <vector>
#include "SubMultiplication.h"
#include "InputNode.h"
#include "OperationNode.h"
#include "Subtraction.h"
#include "Addition.h"
#include "Shift.h"
#include <math.h>
#include <iostream>

using namespace std;

KaratsubaOfman::KaratsubaOfman(Multiplier *multipliers, int nMultipliers)
{
    this->multipliers = multipliers;
    this->nMultipliers = nMultipliers;
}

MultiplicationTree* KaratsubaOfman::dispositions(short lengthX, short lengthY, int *nDispositions)
{
    vector <MultiplicationTree> multiplicationTree;
    MultiplicationTree c;
    int i;

    for(i=0; i<nMultipliers; i++)
    {
        c = dispose(lengthX, lengthY, i);
        if(c.getNSubMultiplications() > 0)
        {
            multiplicationTree.push_back(c);
        }
    }
    if (multiplicationTree.size() > 0)
    {
        *nDispositions = multiplicationTree.size();
        return &multiplicationTree[0];
    }
    else
    {
        *nDispositions = 0;
        return 0;
    }
}

MultiplicationTree KaratsubaOfman::dispose(short lengthX, short lengthY, int index)
{
    short lm;
    InputNode* x1, x0, y1, y0;
    OperationNode* dX, dY, dXdY, x1y1, x1y1, halfMiddle, pMiddle, middle, first, last, root;

    cout << "Karatsuba" << endl;
    cout << multipliers[index].getInputLenght1() << ", " << multipliers[index].getInputLenght2() << endl;

    if (lengthX == lengthY && multipliers[index].getInputLenght1() == multipliers[index].getInputLenght2() && \
    (multipliers[index].getInputLenght1() * 2) > lengthX && lengthX > multipliers[index].getInputLenght1())
    {
        lm = lengthX/2;
        x0 = new InputNode(true, 0, lm);
        x1 = new InputNode(true, lm, lengthX - lm - 2);
        y0 = new InputNode(false, 0, lm);
        y1 = new InputNode(false, lm, lengthY - lm - 2);
        
        //Differenze
        dX = new OperationNode(Subtraction());
        dX->setLeftChild(x1);
        dX->setRightChild(x0);

        dY = new OperationNode(Subtraction());
        dY->setLeftChild(y1);
        dY->setRightChild(y0);

        dXdY = new OperationNode(SubMultiplication(multipliers[index]));
        dXdY->setLeftChild(dX);
        dXdY->setRightChild(dY)
        
        x1y1 = new OperationNode(SubMultiplication(multipliers[index]));
        x1y1->setLeftChild(x1);
        x1y1->setRightChild(y1);

        x0y0 = new OperationNode(SubMultiplication(multipliers[index]));
        x0y0->setLeftChild(x0);
        x0y0->setRightChild(y0);

        halfMiddle = new OperationNode(Addition());
        halfMiddle->setLeftChild(x1y1);
        halfMiddle->setRightChild(x0y0);

        pMiddle = new OperationNode(Subtraction());
        pMiddle->setLeftChild(halfMiddle);
        pMiddle->setRightChild(dXdY);
        
        middle = new OperationNode(Shift(lm));
        middle->setLeftChild(pMiddle);

        first = new OperationNode(Shift(2*lm));
        first->setLeftChild(x1y1);

        last = new OperationNode(Addition());
        last->setLeftChild(first);
        last->setRightChild(x0y0);

        root = new OperationNode(Addition());
        root->setLeftChild(middle);
        root->setRightChild(last);

        return MultiplicationTree(root);
    }
    return MultiplicationTree();
}