#include <iostream>
#include <vector>
#include <math.h>
#include "ProposedTiling.h"
#include "InputNode.h"
#include "SubMultiplication.h"
#include "Subtraction.h"
#include "Addition.h"
#include "Shift.h"

using namespace std;

ProposedTiling::ProposedTiling(Multiplier *multipliers, int nMultiplier)
{
    this->multipliers = multipliers;
    this->nMultipliers = nMultipliers;
}

MultiplicationTree* ProposedTiling::dispositions(short lengthX, short lengthY, int *nDispositions)
{
    vector <MultiplicationTree> multiplicationTree;    
    int i;

    for (i=0; i<nMultipliers;i++)
    {
        multiplicationTree.push_back(dispose(lengthX, lengthY, i));
    }
    if (multiplicationTree.size() > 0)
    {
        *nDispositions = multiplicationTree.size();
        return &multiplicationTree[0];
    }
    else 
    {
        *nDispositions = 0;
        return NULL;
    }
}

MultiplicationTree ProposedTiling::dispose(short x, short y, int index)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    int i, j;
    vector <OperationNode*> operationNodes, multiplicationTreeMapper;
    OperationNode *operationNode, *operationNodeShift;
    InputNode *in1, *in2;
    bool lastv;

    dim1 = multipliers[index].getInputLenght1() - 1;
    dim2 = multipliers[index].getInputLenght2() - 1;
    lastv = false;
    i = 0;
    j = 0;

    if (dim1 > dim2)
    {
        max = dim1;
        min = dim2;
    }
    else
    {
        max = dim2;
        min = dim1;
    }

    if (max != min)
    {
        if (lastv == false)
        {
            for (; (i * min) + max < x; i++)
            {
                in1 = new InputNode(true, ((short) i * min), ((short) min));
                in2 = new InputNode(false, ((short) j * min), ((short) max));
                operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
                operationNodeShift->setLeftChild(operationNode);
                multiplicationTreeMapper.push_back(operationNodeShift);
            }
            in1 = new InputNode(true, ((short) i * min), ((short) x - (i * min)));
            in2 = new InputNode(false, ((short) j * min), ((short) min));
            operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
            operationNodeShift->setLeftChild(operationNode);
            multiplicationTreeMapper.push_back(operationNodeShift);
            j++;
        }
        else
        {
            for (; (j * min) + max < y; j++)
            {
                in1 = new InputNode(true, ((short) i * min), (short)  max);
                in2 = new InputNode(false, ((short) j * min), (short) min);
                operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
                operationNodeShift->setLeftChild(operationNode);
                multiplicationTreeMapper.push_back(operationNodeShift);
            }
            in1 = new InputNode(true, ((short) j * min), ((short) x - (j * min)));
            in2 = new InputNode(false, )
        }
    }
    else
        return MultiplicationTree();
}