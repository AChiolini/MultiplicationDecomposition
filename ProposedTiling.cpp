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
    MultiplicationTree tmph, tmpv;

    for (i=0; i<multipliers.size(); i++)
    {
        tmph = disposeHorizontal(lengthX, lengthY, multipliers[i]);
        tmpv = disposeVertical(lengthX, lengthY, multipliers[i]);
        if (tmph.getRoot() != nullptr)
            multiplicationTrees.push_back(tmph);
        if (tmpv.getRoot() != nullptr)
            multiplicationTrees.push_back(tmpv);
    }
    return multiplicationTrees;
}

MultiplicationTree ProposedTiling::disposeHorizontal(short x, short y, Multiplier multiplier)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    short index1, index2;
    short lX;
    int i, j, minv, minh, a, b;
    bool match;
    bool sub;
    vector <shared_ptr<OperationNode>> operationNodes, tmpArray;
    vector<shared_ptr<InputNode>> inputNodes;
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
    sub = false;

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
/*
        Check directionality and matrix
*/
        if((min >= x && max >= y) || (max >= x && min >= y))
        {
            in1 = make_shared<InputNode>(true, (short) 0, x);
            in2 = make_shared<InputNode>(false, (short) 0, y);
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
            operationNode->setLeftChild(in1);
            operationNode->setRightChild(in2);
            operationNodes.push_back(operationNode);
            match = true;
        }
        if (match == false)
        {
            //Parto dall'orizzontale e creo l'array
            if(max < y) 
            {
                // Posiziono il minimo numero di moltiplicatori sulla VERTICALE dall'input di lunghezza minore
                for(; (i * min) + max <= y; i++)
                {
                    //inputNodes.push_back(make_shared<InputNode>(true, ((short) j * min), ((short) max)));
                    if (x < max)
                        lX = x;
                    else
                        lX = max;
                    index1 = checkExist(true, ((short) j * min), ((short) lX), inputNodes);
                    if (index1 == -1)
                    {
                        in1 = make_shared<InputNode>(true, ((short) j * min), ((short) lX));
                        inputNodes.push_back(in1);
                    }
                    else
                    {
                        in1 = inputNodes[index1];
                    }
                    index2 = checkExist(false, ((short) i * min), ((short) min), inputNodes);
                    if (index2 == -1)
                    {
                        in2 = make_shared<InputNode>(false, ((short) i * min), ((short) min));
                        inputNodes.push_back(in2);
                    }
                    else
                    {
                        in2 = inputNodes[index2];
                    }
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    operationNodeShift = makeShift(in1, in2, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    //Tengo conto di quanti moltiplicatori "sdraiati" ho messo sulla verticale
                    minv++;
                }
                // Aggiungo l'ultimo moltiplicatore dal lato maggiore che sforerà o sarà uguale alla dimensione VERTICALE della moltiplicazione da eseguire
                index1 = checkExist(true, ((short) j * min), ((short) min), inputNodes);
                if (index1 == -1)
                {
                    in1 = make_shared<InputNode>(true, ((short) j * min), ((short) min));
                    inputNodes.push_back(in1);
                }
                else
                {
                    in1 = inputNodes[index1];
                }
                index2 = checkExist(false, ((short) i * min), ((short) y - (i * min)), inputNodes);
                if (index2 == -1)
                {
                    in2 = make_shared<InputNode>(false, ((short) i * min), ((short) y - (i * min)));
                    inputNodes.push_back(in2);
                }
                else
                {
                    in2 = inputNodes[index2];
                }
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                operationNodeShift = makeShift(in1, in2, operationNode);
                operationNodes.push_back(operationNodeShift);
                minh++;

                if(max >= x)
                {
                    in1 = make_shared<InputNode>(true, min, x - min);
                    in2 = make_shared<InputNode>(false, minv * min, y - (minv * min));
                    if(in1.get()->getLength() <= multiplier.getMinInput1() && in2.get()->getLength() <= multiplier.getMinInput2())
                    {
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>());
                        operationNode->setLeftChild(in1);
                        operationNode->setRightChild(in2);
                        operationNodeShift = makeShift(in1, in2, operationNode);
                        operationNodes.push_back(operationNodeShift);
                       // cout << operationNode->isLUT() << endl;
                    }
                    else
                    {
                        cout << "La parte da coprire non è una LUT.\nTODO da decidere cosa fare se scartare o aggiungere il moltiplicatore" << endl;
                        return MultiplicationTree();
                    }
                }
                else
                {
                    // max < x. L'algoritmo continua.
                    //cout << "max < x, L'algoritmo continua" << endl;

                // Posiziono il minimo numero di moltiplicatori sull'ORIZZONTALE partendo dai bit 0 dall'input di lunghezza minore
                    for(j = minh, i = 0; max + (j * min) <= x; j++)
                    {
                        index1 = checkExist(true, ((short) max + ((j-1)*min)), (short) min, inputNodes);
                        if (index1 == -1)
                        {
                            in1 = make_shared<InputNode>(true, ((short) max + ((j-1)*min)), (short) min);
                            inputNodes.push_back(in1);
                        }
                        else
                        {
                            in1 = inputNodes[index1];
                        }
                        index2 = checkExist(false, ((short) i * min), (short) max, inputNodes);
                        if (index2 == -1)
                        {
                            in2 = make_shared<InputNode>(false, ((short) i * min), (short) max);
                            inputNodes.push_back(in2);
                        }
                        else
                        {
                            in2 = inputNodes[index2];
                        }
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                        operationNode->setLeftChild(in1);
                        operationNode->setRightChild(in2);
                        operationNodeShift = makeShift(in1, in2, operationNode);
                        operationNodes.push_back(operationNodeShift);
                        minh++;
                    }
                    
                // Aggiungo l'ultimo moltiplicatore dal lato minimo che sforerà la dimensione della moltiplicazione da eseguire
                    index1 = checkExist(true, ((short) max + (j-1) * min), ((short) x - max - (j-1)*min), inputNodes);
                    if (index1 == -1)
                    {
                        in1 = make_shared<InputNode>(true, ((short) max + (j-1) * min), ((short) x - max - (j-1)*min));
                        inputNodes.push_back(in1);
                    }
                    else
                    {
                        in1 = inputNodes[index1];
                    }
                    index2 = checkExist(false, ((short) i*min), ((short) max), inputNodes);
                    if (index2 == -1)
                    {
                        in2 = make_shared<InputNode>(false, ((short) i*min), ((short) max));
                        inputNodes.push_back(in2);
                    }
                    else
                    {
                        in2 = inputNodes[index2];
                    }
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    operationNodeShift = makeShift(in1, in2, operationNode);
                    operationNodes.push_back(operationNodeShift);

                // Posiziono il moltiplicatore più estremo
                    i = minv;
                    j = minh;
                    index1 = checkExist(true, ((short) j * min), ((short) x - (j*min)), inputNodes);
                    if (index1 == -1)
                    {
                        in1 = make_shared<InputNode>(true, ((short) j * min), ((short) x - (j*min))); 
                        inputNodes.push_back(in1);
                    }
                    else
                    {
                        in1 = inputNodes[index1];
                    }
                    index2 = checkExist(false, ((short) max + ((i-1)*min)), ((short) min - ((i*min) + max - y)), inputNodes);
                    if (index2 == -1)
                    {
                        in2 = make_shared<InputNode>(false, ((short) max + ((i-1)*min)), ((short) min - ((i*min) + max - y)));
                        inputNodes.push_back(in2);
                    }
                    else
                    {
                        in2 = inputNodes[index2];
                    }
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    operationNodeShift = makeShift(in1, in2, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    
                // Posiziono i moltiplicatori rimanenti sulla verticale e sull'orizzontale
                    for(i = minv - 1, j = minh; i > 0; i--)
                    {
                        index1 = checkExist(true, ((short) j * min), (short) x - (j*min), inputNodes);
                        if (index1 == -1)
                        {
                            in1 = make_shared<InputNode>(true, ((short) j * min), (short) x - (j*min));
                            inputNodes.push_back(in1);
                        }
                        else
                        {
                            in1 = inputNodes[index1];
                        }
                        index2 = checkExist(false, ((short) max + ((i-1)*min)), ((short) min), inputNodes);
                        if (index2 == -1)
                        {
                            in2 = make_shared<InputNode>(false, ((short) max + ((i-1)*min)), ((short) min));
                            inputNodes.push_back(in2);
                        }
                        else
                        {
                            in2 = inputNodes[index2];
                        }
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                        operationNode->setLeftChild(in1);
                        operationNode->setRightChild(in2);
                        operationNodeShift = makeShift(in1, in2, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    for(i = minv, j = minh - 1; j > 0; j--)
                    {
                        index1 = checkExist(true, ((short) j * min), ((short) min), inputNodes);
                        if (index1 == -1)
                        {
                            in1 = make_shared<InputNode>(true, ((short) j * min), ((short) min));
                            inputNodes.push_back(in1);
                        }
                        else
                        {
                            in1 = inputNodes[index1];
                        }
                        index2 = checkExist(false, ((short) i * min), ((short) y - (i * min)), inputNodes);
                        if (index2 == -1)
                        {
                            in2 = make_shared<InputNode>(false, ((short) i * min), ((short) y - (i * min)));
                            inputNodes.push_back(in2);
                        }
                        else
                        {
                            in2 = inputNodes[index2];
                        }
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                        operationNode->setLeftChild(in1);
                        operationNode->setRightChild(in2);
                        operationNodeShift = makeShift(in1, in2, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }

                // Verifico che la parte centrale rimanente sia mappabile tramite LUT.
                // Se non lo è allora scarto la soluzione
                    if((minh * min) > max && (minv * min) > max)
                    {
                        in1 = make_shared<InputNode>(true, ((short) max), ((short) (minh*min) - max));
                        in2 = make_shared<InputNode>(false, ((short) max), ((short) (minv*min) - max));
                    }
                    else if ((minh * min) < max && (minv * min) < max)
                    {
                        in1 = make_shared<InputNode>(true, ((short) min), ((short) (max - min)));
                        in2 = make_shared<InputNode>(false, ((short) min), ((short) (max - min)));
                    }
                    else if ((minv * min) > max && (minh * min) < max)
                    {
                        in1 = make_shared<InputNode>(true, (short) min, (short) max - min);
                        in2 = make_shared<InputNode>(false, (short) max, (short) (minv * min) - max);
                    }
                    else if ((minh * min) > max && (minv * min) < max)
                    {
                        in1 = make_shared<InputNode>(true, (short) max, (short) (minh * min) - max);
                        in2 = make_shared<InputNode>(false, (short) min, (short) max - min);
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
            }
            else
                return MultiplicationTree();   
        }
        // Creo l'albero di somme di moltiplicazioni
        cout << "size: " << operationNodes.size() << operationNodes[0] << endl;
        while(operationNodes.size() > 0 && operationNodes.size() != 1)
        {	
            for(i = 0; i < operationNodes.size(); i = i + 2)
            {
                if (i + 1 < operationNodes.size())
                {
                    if (i + 1 == operationNodes.size() - 1 && ((minh * min > max && minv * min < max) || (minh*min < max && minv * min > max)) && operationNodes.size() % 2 == 0 && sub == false)
                    {
                        operationNode = make_shared<OperationNode>(make_shared<Subtraction>());
                        sub = true;
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
        
        return MultiplicationTree(operationNodes[0], "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", (int) x + 1, (int) y + 1);
    }
    else    
        return MultiplicationTree();
}

MultiplicationTree ProposedTiling::disposeVertical(short x, short y, Multiplier multiplier)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    short index1, index2;
    short lX, lY;
    int i, j, minv, minh, a, b;
    bool sub;
    vector <shared_ptr<OperationNode>> operationNodes, tmpArray;
    vector<shared_ptr<InputNode>> inputNodes;
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
        //Il match è già stato trovato con la disposizione in orizzontale. È inutile ripetere la soluzione
        if(((min >= x && max >= y) || (max >= x && min >= y)) == false)
        {
            if (max >= y)
            {
                if(x > min)
                {
                    in1 = make_shared<InputNode>(true, (short) 0, min);
                    in2 = make_shared<InputNode>(false, (short) 0, y);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    operationNodeShift = makeShift(in1, in2, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    for(i = 1; min + (i * max) < x; i++)
                    {
                        in1 = make_shared<InputNode>(true, (short) min + (i * max), (short) max);
                        in2 = make_shared<InputNode>(false, (short) 0, min);
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                        operationNode->setLeftChild(in1);
                        operationNode->setRightChild(in2);
                        operationNodeShift = makeShift(in1, in2, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    in1 = make_shared<InputNode>(true, (short) min + ((i-1) * max), (short) max - (min + (i * max) - y));
                    in2 = make_shared<InputNode>(false, (short) 0, min);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    operationNodeShift = makeShift(in1, in2, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    in1 = make_shared<InputNode>(true, min, x - min);
                    in2 = make_shared<InputNode>(false, min, y - min);
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
            }
            else
            {
                cout << "max < y" << endl;
                return MultiplicationTree();
            }
            // Creo l'albero di somme di moltiplicazioni
            while(operationNodes.size() > 0 && operationNodes.size() != 1)
            {   
                for(i = 0; i < operationNodes.size(); i = i + 2)
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
            
            return MultiplicationTree(operationNodes[0], "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", (int) x + 1, (int) y + 1);
        }
        else
            return MultiplicationTree();
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

short ProposedTiling::checkExist(bool firstInput, short start, short length, vector<shared_ptr<InputNode>> inputNodes)
{
    short i;
    for (i = 0; i < inputNodes.size(); i++)
    {
        if (inputNodes[i].get()->isFirstInput() == firstInput && inputNodes[i].get()->getStart() == start && inputNodes[i].get()->getLength() == length)
        {
            //cout << i << endl;
            return i;
        }
    }
    return -1;
}