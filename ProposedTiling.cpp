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
    bool match;
    vector <shared_ptr<OperationNode>> operationNodes, tmpArray;
    shared_ptr<OperationNode> operationNode, operationNodeShift;
    shared_ptr<InputNode> in1, in2;
    SubMultiplication *tmp;

    dim1 = multiplier.getInputLength1() - 1;
    dim2 = multiplier.getInputLength2() - 1;
    i = 0;
    j = 0;
    minv = 0;
    minh = 0;
    x--;
    y--;
    match = false;

    // Proposed tiling is possible only with rectangular multipliers
    if(multiplier.getInputLength1() != multiplier.getInputLength2())
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
        if(min == x && max == y)
        {
            in1 = make_shared<InputNode>(true, (short) 0, min);
            in2 = make_shared<InputNode>(false, (short) 0, max);
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodes.push_back(operationNode);
            match = true;
        }
        else if (max == x && min == y)
        {
            in1 = make_shared<InputNode>(true, (short) 0, (short) max);
            in2 = make_shared<InputNode>(false, (short) 0, (short) min);
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodes.push_back(operationNode);
            match = true;
        }
        if (!match)
        {
            // Posiziono il minimo numero di moltiplicatori sulla verticale dall'input di lunghezza minore
            for(; (i * min) + max <= y; i++)
            {
                in1 = make_shared<InputNode>(true, ((short) j * min), ((short) max));
                in2 = make_shared<InputNode>(false, ((short) i * min), ((short) min));
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = makeShift(in1, in2, operationNode);
                operationNodes.push_back(operationNodeShift);
                minv++;
            }
            // Aggiungo l'ultimo moltiplicatore dal lato maggiore che sforerà la dimensione della moltiplicazione da eseguire 
            in1 = make_shared<InputNode>(true, ((short) j * min), ((short) min));
            in2 = make_shared<InputNode>(false, ((short) i * min), ((short) y - (i * min)));
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = makeShift(in1, in2, operationNode);
            operationNodes.push_back(operationNodeShift);
            minh++;

            // Posiziono il minimo numero di moltiplicatori sull'orizzontale partendo dai bit 0 dall'input di lunghezza minore
            for(j = minh, i = 0; max + (j * min) <= x; j++)
            {
                in1 = make_shared<InputNode>(true, ((short) max + ((j-1)*min)), (short) min);
                in2 = make_shared<InputNode>(false, ((short) i * min), (short) max);
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = makeShift(in1, in2, operationNode);
                operationNodes.push_back(operationNodeShift);
                minh++;
            }
            // Aggiungo l'ultimo moltiplicatore dal lato minimo che sforerà la dimensione della moltiplicazione da eseguire
            in1 = make_shared<InputNode>(true, ((short) max + (j-1) * min), ((short) x - max - (j-1)*min));
            in2 = make_shared<InputNode>(false, ((short) i*min), ((short) max));
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = makeShift(in1, in2, operationNode);
            operationNodes.push_back(operationNodeShift);

            // Posiziono il moltiplicatore più estremo
            i = minv;
            j = minh;
            in1 = make_shared<InputNode>(true, ((short) j * min), ((short) x - (j*min))); 
            in2 = make_shared<InputNode>(false, ((short) max + ((i-1)*min)), ((short) min - ((i*min) + max - y)));
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodeShift = makeShift(in1, in2, operationNode);
            operationNodes.push_back(operationNodeShift);
            
            // Posiziono i moltiplicatori rimanenti sulla verticale e sull'orizzontale
            for(i = minv - 1, j = minh; i > 0; i--)
            {
                in1 = make_shared<InputNode>(true, ((short) j * min), (short) x - (j*min));
                in2 = make_shared<InputNode>(false, ((short) max + ((i-1)*min)), ((short) min));
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = makeShift(in1, in2, operationNode);
                operationNodes.push_back(operationNodeShift);
            }
            for(i = minv, j = minh - 1; j > 0; j--)
            {
                in1 = make_shared<InputNode>(true, ((short) j * min), ((short) min));
                in2 = make_shared<InputNode>(false, ((short) i * min), ((short) y - (i * min)));
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = makeShift(in1, in2, operationNode);
                operationNodes.push_back(operationNodeShift);
            }

            // Verifico che la parte centrale rimanente sia mappabile tramite LUT.
            // Se non lo è allora scarto la soluzione
            if((minh*min) > max && (minv*min) > max)
            {
                in1 = make_shared<InputNode>(true, ((short) max), ((short) (minh*min) - max));
                in2 = make_shared<InputNode>(false, ((short) max), ((short) (minv*min) - max));
            }
            else
            {
                in1 = make_shared<InputNode>(true, ((short) min), ((short) (max - min)));
                in2 = make_shared<InputNode>(false, ((short) min), ((short) (max - min)));
            }

            if(in1.get()->getLength() < multiplier.getMinInput1() && in2.get()->getLength() < multiplier.getMinInput2())
            {
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>());
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = makeShift(in1, in2, operationNode);
                operationNodes.push_back(operationNodeShift);
            }
            else
                return MultiplicationTree();
        }
        // Creo l'albero di somme di moltiplicazioni
        while(operationNodes.size() > 0 && operationNodes.size() != 1)
        {	
            for(i = 0; i < operationNodes.size(); i = i+2)
            {
                if (i + 1 < operationNodes.size())
                {
                    if (i + 1 == operationNodes.size() - 1 && ((minh * min > max && minv * min < max) || (minh*min < max && minv * min > max)))
                    {
                        operationNode = make_shared<OperationNode>(make_shared<Subtraction>());
                    }
                    else
                    {
                        operationNode = make_shared<OperationNode>(make_shared<Addition>());
                    }
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
        
        return MultiplicationTree(operationNodes[0], "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", (int) x, (int) y);
    }
    else    
        return MultiplicationTree();
}

shared_ptr<OperationNode> ProposedTiling::makeShift(shared_ptr<InputNode> in1, shared_ptr<InputNode> in2, shared_ptr<OperationNode> operationNode)
{
    shared_ptr<OperationNode> operationNodeShift;
    if(in1->getStart() + in2->getStart() > 0)
    {
        operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
        operationNodeShift->setLeftChild(operationNode);
        return operationNodeShift;
    }
    else
    {
        return operationNode;
    }
}
