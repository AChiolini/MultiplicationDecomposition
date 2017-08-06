#include <iostream>
#include <math.h>
#include "ProposedTiling.h"
#include "InputNode.h"
#include "SubMultiplication.h"
#include "Subtraction.h"
#include "Addition.h"
#include "Shift.h"

using namespace std;

ProposedTiling::ProposedTiling(vector<Multiplier> multipliers)
{
    this->multipliers = multipliers;
}

vector<MultiplicationTree> ProposedTiling::dispositions(short lengthX, short lengthY)
{
    vector <MultiplicationTree> multiplicationTrees;    
    int i;
    MultiplicationTree tmp;

    for (i=0; i<multipliers.size(); i++)
    {
        tmp = dispose(lengthX, lengthY, multipliers[i]);
        if (tmp.getRoot() != nullptr)
            multiplicationTrees.push_back(tmp);
    }
    return multiplicationTrees;
}

MultiplicationTree ProposedTiling::dispose(short x, short y, Multiplier multiplier)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    int i, j, minv, minh;
    vector <shared_ptr<OperationNode>> operationNodes, multiplicationTreeMapper, tmpArray;
    shared_ptr<OperationNode> operationNode, operationNodeShift;
    shared_ptr<InputNode> in1, in2;

    dim1 = multiplier.getInputLenght1() - 1;
    dim2 = multiplier.getInputLenght2() - 1;
    i = 0;
    j = 0;
    minv = 0;
    minh = 0;

    if(multiplier.getInputLenght1() != multiplier.getInputLenght2())
    {
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

        for(; (i * min) + max < y; i++)
        {
            in1 = make_shared<InputNode>(true, ((short) j * min), ((short) max));
            in2 = make_shared<InputNode>(false, ((short) i * min), ((short) min));
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
            operationNodeShift->setLeftChild(operationNode);
            operationNodes.push_back(operationNodeShift);
            minv++;
        }
        in1 = make_shared<InputNode>(true, ((short) j * min), ((short) min));
        in2 = make_shared<InputNode>(false, ((short) i * min), ((short) y - (i * min)));
        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        operationNode->setLeftChild(in1);
        operationNode->setRightChild(in2);
        operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
        operationNodeShift->setLeftChild(operationNode);
        operationNodes.push_back(operationNodeShift);
        minh++;

        for(j = minh, i = 0; max + (j * min) < x; j++)
        {
            in1 = make_shared<InputNode>(true, ((short) max + ((j-1)*min)), (short) min);
            in2 = make_shared<InputNode>(false, ((short) i * min), (short) max);
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
            operationNodeShift->setLeftChild(operationNode);
            operationNodes.push_back(operationNodeShift);
            minh++;
        }
        in1 = make_shared<InputNode>(true, ((short) max + (j-1) * min), ((short) x - max - (j-1)*min));
        in2 = make_shared<InputNode>(false, ((short) i*min), ((short) max));
        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        operationNode->setLeftChild(in1);
        operationNode->setRightChild(in2);
        operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
        operationNodeShift->setLeftChild(operationNode);
        operationNodes.push_back(operationNodeShift);

        i = minv;
        j = minh;
        in1 = make_shared<InputNode>(true, ((short) j * min), ((short) x - (j*min))); 
        in2 = make_shared<InputNode>(false, ((short) min - ((i*min) + max - y)), ((short) y - ((i-1)*min) - max));
        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
        operationNode->setLeftChild(in1);
        operationNode->setRightChild(in2);
        operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
        operationNodeShift->setLeftChild(operationNode);
        operationNodes.push_back(operationNodeShift);
        

        for(i = minv - 1, j = minh; i > 0; i--)
        {
            in1 = make_shared<InputNode>(true, ((short) j * min), (short) x - (j*min));
            in2 = make_shared<InputNode>(false, ((short) max + ((i-1)*min)), ((short) min));
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
            operationNodeShift->setLeftChild(operationNode);
            operationNodes.push_back(operationNodeShift);
        }
        for(i = minv, j = minh - 1; j > 0; j--)
        {
            in1 = make_shared<InputNode>(true, ((short) j * min), ((short) min));
            in2 = make_shared<InputNode>(false, ((short) i * min), ((short) y - (i * min)));
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
            operationNodeShift->setLeftChild(operationNode);
            operationNodes.push_back(operationNodeShift);
        }

        while(operationNodes.size() > 0 && operationNodes.size() != 1)
        {	
            for(i = 0; i < operationNodes.size(); i = i+2)
            {
                if (i + 1 < operationNodes.size())
                {
                    operationNode = make_shared<OperationNode>(make_shared<Addition>());
                    operationNode->setLeftChild(operationNodes[i]);
                    operationNode->setRightChild(operationNodes[i+1]);
                    tmpArray.push_back(operationNode);
                }
                else
                {
                    tmpArray.push_back(operationNodes[i]);
                }
            }
            operationNodes.swap(tmpArray);
            tmpArray.clear();
        }
        return MultiplicationTree(operationNodes[0], "Proposed tiling (" + to_string(multiplier.getInputLenght1()) + "x" + to_string(multiplier.getInputLenght2()) + ")");
    }
    else    
        return MultiplicationTree();
}