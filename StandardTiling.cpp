#include <iostream>
#include <vector>
#include <math.h>
#include "StandardTiling.h"
#include "InputNode.h"
#include "SubMultiplication.h"
#include "Subtraction.h"
#include "Addition.h"
#include "Shift.h"

using namespace std;

StandardTiling::StandardTiling(Multiplier *multipliers, int nMultipliers)
{
    this->multipliers = multipliers;
    this->nMultipliers = nMultipliers;
}

MultiplicationTree* StandardTiling::dispositions(short lengthX, short lengthY, int *nDispositions)
{
	vector <MultiplicationTree> multiplicationTree;    
	int i;
	MultiplicationTree c;

    for (i=0; i<nMultipliers;i++)
    {
		c = dispose(lengthX, lengthY, i);
		if (c.getRoot() != NULL)
        	multiplicationTree.push_back(c);
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

MultiplicationTree StandardTiling::dispose(short x, short y, int index)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    //int levels, delay;
    int nmaxv, nminv, countv, nmaxh, nminh, counth, i, j, k, n, nmaxtmp, lX, lY;
	int w;
    bool match;
    vector <OperationNode*> operationNodes, multiplicationTreeMapper;
	OperationNode *operationNode, *operationNodeShift;
	InputNode *in1, *in2;

    dim1 = multipliers[index].getInputLenght1() - 1;
    dim2 = multipliers[index].getInputLenght2() - 1;
    match = false;
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
				lX = max - ((i + 1) * max) + x;
			else
				lX = max;
			for (j = 0; j * max < y; j++)
			{
				if ((j + 1) * max > y)
					lY = max - ((j + 1) * max) + y;
				else
					lY = max;
				in1 = new InputNode(true, ((short) (i * max)), (short) lX);
				in2 = new InputNode(false, ((short) (j * max)), (short) lY);
				operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
				operationNode->setLeftChild(in1);
				operationNode->setRightChild(in2);
				//subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * max)), (short) lX, (short) lY, multipliers[index]));
				//Aggiungo al vettore la moltiplicazione con il rispettivo shift
				operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
				operationNodeShift->setLeftChild(operationNode);
				operationNodes.push_back(operationNodeShift);
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
					match = true;
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
					match = true;
				} while (match == false && nmaxh > 0);
			if (match == false)
			{
				nmaxh = nmaxtmp;
				nminh = 0;
			}
			for (i = 0; i < nmaxh; i++)
			{
				if ((i + 1) * max > x)
					lX = max - ((i + 1) * max) + x;
					else
					lX = max;
				for (j = 0; j * min < y; j++)
				{
					if ((j + 1) * min > y)
						lY = min - ((j + 1) * min) + y;
					else
						lY = min;
					in1 = new InputNode(true, ((short) (i * max)), (short) lX);
					in2 = new InputNode(false, ((short) (j * max)), (short) lY);
					operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
					operationNode->setLeftChild(in1);
					operationNode->setRightChild(in2);
					//subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * min)), (short) lX, (short) lY, multipliers[index]));
					operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
					operationNodeShift->setLeftChild(operationNode);
					operationNodes.push_back(operationNodeShift);
				}
	    	}
			for (k = 0; k < nminh; k++)
			{
				if ((i * max) + ((k + 1) * min) > x)
					lX = min - ((i * max) + ((k + 1) * min)) + x;
					else
					lX = min;
				for (j = 0; j * max < y; j++)
				{
					if ((j + 1) * max > y)
						lY = max - ((j + 1) * max) + y;
					else
						lY = max;
					in1 = new InputNode(true, ((short) ((i * max) + (k * min))), (short) lX);
					in2 = new InputNode(false, ((short) (j * max)), (short) lY);
					operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
					operationNode->setLeftChild(in1);
					operationNode->setRightChild(in2);
					//subMultiplications.push_back (SubMultiplication (((short) ((i * max) + (k * min))), ((short) (j * max)), (short) lX, (short) lY, multipliers[index]));	    
					operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
					operationNodeShift->setLeftChild(operationNode);
					operationNodes.push_back(operationNodeShift);

				} 
	    	}	
		}
        else
        {
            //match verticale
            for (i = 0; i < nmaxv; i++)
            {
                if ((i + 1) * max > y)
                    lY = max - ((i + 1) * max) + y;
                else
                    lY = max;
                for (j = 0; j * min < x; j++)
                {
                    if ((j + 1) * min > x)
                        lX = min - ((j + 1) * min) + x;
                    else
                    	lX = min;
                    in1 = new InputNode(true, ((short) (j * min)), (short) lX);
                    in2 = new InputNode(false, ((short) (i * max)), (short) lY);
                    operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    //subMultiplications.push_back (SubMultiplication (((short) (j * min)), ((short) (i * max)), (short) lX, (short) lY, multipliers[index]));
					operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
					operationNodeShift->setLeftChild(operationNode);
					operationNodes.push_back(operationNodeShift);

                }
            }
            for (k = 0; k < nminv; k++)
            {
                if ((i * max) + ((k + 1) * min) > y)
                    lY = min - ((i * max) + ((k + 1) * min)) + y;
                else
                    lY = min;
                for (j = 0; j * max < x; j++)
                {
                    if ((j + 1) * max > x)
                        lX = max - ((j + 1) * max) + x;
                    else
                        lX = max;
                    in1 = new InputNode(true, ((short) (j * max)), (short) lX);
                    in2 = new InputNode(false, ((short) ((i * max) + (k * min))), (short) lY);
                    operationNode = new OperationNode(new SubMultiplication(multipliers[index]));
                    operationNode->setLeftChild(in1);
                    operationNode->setRightChild(in2);
                    //subMultiplications.push_back (SubMultiplication (((short) (j * max)), ((short) ((i * max) + (k * min))), (short) lX, (short) lY, multipliers[index]));
					operationNodeShift = new OperationNode(new Shift(in1->getStart() + in2->getStart()));
					operationNodeShift->setLeftChild(operationNode);
					operationNodes.push_back(operationNodeShift);

                }		    
            }
        }
    }
    /*if (operationNodes.size() > 0)
    {
		for (levels = 0; pow (2.0, levels) < subMultiplications.size(); levels++);
		delay = levels + multipliers[index].getDelay();
    }
    else
		delay = 0;
    for (i = 0; i < operationNodes.size(); i++)
    {
	cout << "(" << subMultiplications[i].getX() << ", " << subMultiplications[i].getY() << ", ";
	cout << subMultiplications[i].getLengthX() << ", " << subMultiplications[i].getLengthY() << ")" << endl;
    }
    cout << "Delay: " << delay << endl;
    return Configuration(&subMultiplications[0], subMultiplications.size(), delay);
	*/
	if(operationNodes.size() > 0)
	{
		for(i = 0; i < operationNodes.size(); i++)
		{
			w = multiplicationTreeMapper.size();
			if(operationNodes[i]->getOperation()->getOperationType() == SHIFT)
			{
				if(w == 0)
				{
					operationNode = new OperationNode(new Addition());
					operationNode->setLeftChild(operationNodes[i]);
					multiplicationTreeMapper.push_back(operationNode);
				}
				else
				{
					if(multiplicationTreeMapper[w-1]->getRightChild() == NULL)
						multiplicationTreeMapper[w-1]->setRightChild(operationNodes[i]);
					else
					{
						operationNode = new OperationNode(new Addition());
						operationNode->setLeftChild(multiplicationTreeMapper[w-1]);
						operationNode->setRightChild(operationNodes[i]);
						multiplicationTreeMapper.push_back(operationNode);
					}
				}
			}
		}
		w = multiplicationTreeMapper.size();
		if(multiplicationTreeMapper[w-1]->getRightChild()!=NULL && multiplicationTreeMapper[w-1]->getOperation()->getOperationType()== ADDITION)
			return MultiplicationTree(multiplicationTreeMapper[w-1]);
	}
	return MultiplicationTree();
}