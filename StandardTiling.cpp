#include <iostream>
#include <math.h>
#include "StandardTiling.h"
#include "InputNode.h"
#include "SubMultiplication.h"
#include "Subtraction.h"
#include "Addition.h"
#include "Shift.h"

using namespace std;

StandardTiling::StandardTiling(vector<Multiplier> multipliers)
{
    this->multipliers = multipliers;
}

vector <MultiplicationTree> StandardTiling::dispositions(short lengthX, short lengthY)
{
    vector <MultiplicationTree> multiplicationTrees;    
    int i;
    MultiplicationTree tmp;

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

MultiplicationTree StandardTiling::dispose(short x, short y, Multiplier multiplier)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    int nmaxv, nminv, countv, nmaxh, nminh, counth, i, j, k, n, nmaxtmp, lX, lY;
    int w;
    bool match;
    vector <shared_ptr<OperationNode>> operationNodes, tmpArray;
    shared_ptr<OperationNode> operationNode, operationNode2;
    shared_ptr<InputNode> in1, in2;

    dim1 = multiplier.getInputLenght1() - 1;
    dim2 = multiplier.getInputLenght2() - 1;
    match = false;
    x--;
    y--;
    //Occorre controllare se la moltiplicazione è abbastanza grande per un moltiplicatore (SOGLIE)
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
    if (max == min)
    {
        //se il moltiplicatore è un quadrato mappo tutto fino a che non copro tutta la moltiplicazione
        for (i = 0; i * max < x; i++)
        {
            if ((i + 1) * max > x)
            {
                lX = max - ((i + 1) * max) + x;
            }			
            else
            {
                lX = max;
            }
            for (j = 0; j * max < y; j++)
            {
                if ((j + 1) * max > y)
                {		
                    lY = max - ((j + 1) * max) + y;
                }
                else
                {
                    lY = max;
                }
                in1 = make_shared<InputNode>(true, ((short) (i * max)), (short) lX);
                in2 = make_shared<InputNode>(false, ((short) (j * max)), (short) lY);
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                operationNode->setLeftChild(in1);
                operationNode->setRightChild(in2);
                if (in1->getStart() + in2->getStart() > 0)
		        {
                    operationNode2 = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
                    operationNode2->setLeftChild(operationNode);
                    operationNodes.push_back(operationNode2);
                }
                else
                {
                    operationNodes.push_back(operationNode);
                }
            }
        }
    }
    else
    {
        if (x != y)
        {
            //se la moltiplicazione ha due ingressi di lunghezza diversa controllo prima se posso matchare la verticale
            for (countv = 0, nmaxv = 0; countv < y; countv = countv + max, nmaxv++);
            do
            {
                nmaxv--;
                for (countv = nmaxv * max, nminv = 0; countv < y;  countv = countv + min, nminv++);
                if (countv == y)
		        {
                    match = true;
                }
            } while (match == false && nmaxv > 0);
        }
        if (match == false)
        {
            //se non posso mappo l'orizzontale
            for (counth = 0, nmaxh = 0; counth < x; counth = counth + max, nmaxh++);
            nmaxtmp = nmaxh;
            do
            {
                nmaxh--;
                for (counth = nmaxh * max, nminh = 0; counth < x;  counth = counth + min, nminh++);
                if (counth == x)
                {
                    match = true;
                }
            } while (match == false && nmaxh > 0);
            if (match == false)
            {
                nmaxh = nmaxtmp;
                nminh = 0;
            }
            for (i = 0; i < nmaxh; i++)
            {
                if ((i + 1) * max > x)
                {
                    lX = max - ((i + 1) * max) + x;
                }
                else
                {
                    lX = max;
                }
                for (j = 0; j * min < y; j++)
                {
                    if ((j + 1) * min > y)
                    {
                        lY = min - ((j + 1) * min) + y;
                    }
                    else
                    {
                        lY = min;
                    }
                    in1 = make_shared<InputNode>(true, ((short) (i * max)), (short) lX);
                    in2 = make_shared<InputNode>(false, ((short) (j * max)), (short) lY);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    if (in1->getStart() + in2->getStart() > 0)
		            {
                        operationNode2 = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
                        operationNode2->setLeftChild(operationNode);
                        operationNodes.push_back(operationNode2);
                    }
                    else
                    {
                        operationNodes.push_back(operationNode);
                    }
                }
            }
            for (k = 0; k < nminh; k++)
            {
                if ((i * max) + ((k + 1) * min) > x)
                {
                    lX = min - ((i * max) + ((k + 1) * min)) + x;
                }
                else
                {
                    lX = min;
                }
                for (j = 0; j * max < y; j++)
                {
                    if ((j + 1) * max > y)
                    {
                        lY = max - ((j + 1) * max) + y;
                    }
                    else
                    {
                        lY = max;
                    }
			//NOTA BENE
			//NOTA BENE
			//NOTA BENE
			//Creare una funzione per questa parte in modo da semplificare il codice
                    in1 = make_shared<InputNode>(true, ((short) ((i * max) + (k * min))), (short) lX);
                    in2 = make_shared<InputNode>(false, ((short) (j * max)), (short) lY);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    if (in1->getStart() + in2->getStart() > 0)
		    {
                        operationNode2 = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
                        operationNode2->setLeftChild(operationNode);
                        operationNodes.push_back(operationNode2);
                    }
                    else
                    {
                        operationNodes.push_back(operationNode);
                    }
                } 
            }	
        }
        else
        {
            //match verticale
            for (i = 0; i < nmaxv; i++)
            {
                if ((i + 1) * max > y)
                {
                    lY = max - ((i + 1) * max) + y;
                }
                else
                {
                    lY = max;
                }
                for (j = 0; j * min < x; j++)
                {
                    if ((j + 1) * min > x)
                    {
                        lX = min - ((j + 1) * min) + x;
                    }
                    else
                    {
                    	lX = min;
                    }
                    in1 = make_shared<InputNode>(true, ((short) (j * min)), (short) lX);
                    in2 = make_shared<InputNode>(false, ((short) (i * max)), (short) lY);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    if (in1->getStart() + in2->getStart() > 0)
		    {
                        operationNode2 = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
                        operationNode2->setLeftChild(operationNode);
                        operationNodes.push_back(operationNode2);
                    }
                    else
                    {
                        operationNodes.push_back(operationNode);
                    }
                }
            }
            for (k = 0; k < nminv; k++)
            {
                if ((i * max) + ((k + 1) * min) > y)
                {
                    lY = min - ((i * max) + ((k + 1) * min)) + y;
                }
                else
                {
                    lY = min;
                }
                for (j = 0; j * max < x; j++)
                {
                    if ((j + 1) * max > x)
                    {
                        lX = max - ((j + 1) * max) + x;
                    }
                    else
                    {
                        lX = max;
                    }
                    in1 = make_shared<InputNode>(true, ((short) (j * max)), (short) lX);
                    in2 = make_shared<InputNode>(false, ((short) ((i * max) + (k * min))), (short) lY);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    if (in1->getStart() + in2->getStart() > 0)
		    {
                        operationNode2 = make_shared<OperationNode>(make_shared<Shift>(in1->getStart() + in2->getStart()));
                        operationNode2->setLeftChild(operationNode);
                        operationNodes.push_back(operationNode2);
                    }
                    else
                    {
                        operationNodes.push_back(operationNode);
                    }
                }		    
            }
        }
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
    return MultiplicationTree(operationNodes[0], "Standard tiling (" + to_string(multiplier.getInputLenght1()) + "x" + to_string(multiplier.getInputLenght2()) + ")");
}
