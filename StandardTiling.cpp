#include <iostream>
#include <math.h>
#include "StandardTiling.h"
#include "InputNode.h"
#include "SubMultiplication.h"
#include "Subtraction.h"
#include "Addition.h"

using namespace std;

StandardTiling::StandardTiling(vector<Multiplier> multipliers)
{
    this->multipliers = multipliers;
}

vector <MultiplicationTree> StandardTiling::dispositions(int length_x, int length_y)
{
    vector <MultiplicationTree> multiplicationTrees;    
    int i;
    MultiplicationTree tmp;

    for(i = 0; i < multipliers.size(); i++)
    {
        tmp = dispose (length_x, length_y, multipliers[i]);
        if(tmp.getRoot() != nullptr)
        {
            multiplicationTrees.push_back(tmp);
        }
    }
    return multiplicationTrees;
}

MultiplicationTree StandardTiling::dispose(int x, int y, Multiplier multiplier)
{
    Link first_operand, second_operand;
    shared_ptr<InputNode> input1, input2;
    shared_ptr<OperationNode> root;

    // Pre-checks
    // Both lengths must be greater than 1, otherwise there aren't enough bit for the multiplication.
    if(x <= 1 || y <= 1)
    {
        return MultiplicationTree();
    }
    // Both lengths must be greater than both minimum lengths of the multiplier, otherwise it's all mapped in a LUT.
    // CHIEDERE AL PROFF LA CONDIZIONE SULLA SOGLIA
    if(((x - 1) < multiplier.getMinInput1() && (y - 1) < multiplier.getMinInput2()) || \
       ((x - 1) < multiplier.getMinInput2() && (y - 1) < multiplier.getMinInput1()))
    {
        input1 = make_shared<InputNode>(true, x);
        input2 = make_shared<InputNode>(false, y);
        first_operand = Link(input1, 0, x - 1, false);
        second_operand = Link(input2, 0, y - 1, false);
        root = make_shared<OperationNode>(make_shared<SubMultiplication>(), first_operand, second_operand);
        return MultiplicationTree(root, "LUT multiplication (Standard tiling disposition)", x, y);
    }
    // For simplicity we dived the dispose function in 3 function: one for a square multiplier, one for a rectangular multiplier
    // in a square multiplication and one for a rectangular multiplier in a rectangular multiplication. In this way there will be
    // more code but simple and modifiable in an easy way.
    if(multiplier.getInputLength1() == multiplier.getInputLength2())
    {
        return disposeSquareSquare(x, y, multiplier);
    }
    else
    {
        if(x == y)
        {
            return disposeRectangleSquare(x, y, multiplier);
        }
        else
        {
            return disposeRectangleRectangle(x, y, multiplier);
        }
    }
}

MultiplicationTree StandardTiling::disposeSquareSquare(int x, int y, Multiplier multiplier)
{
    int i, j, dim, length_x, length_y;
    shared_ptr<InputNode> input1, input2;
    Link first_operand, second_operand;
    vector <shared_ptr<OperationNode>> operation_nodes;
    
    input1 = make_shared<InputNode>(true, x);
    input2 = make_shared<InputNode>(false, y);
    dim = multiplier.getInputLength1() - 1;
    for(i = 0; i * dim < (x - 1); i++)
    {
        if((i + 1) * dim > (x - 1))
        {
            length_x = dim - ((i + 1) * dim) + (x - 1);
        }
        else
        {
            length_x = dim;
        }
        for(j = 0; j * dim < (y - 1); j++)
        {
            if((j + 1) * dim > (y - 1))
            {
                length_y = dim - ((j + 1) * dim) + (y - 1);
            }
            else
            {
                length_y = dim;
            }
            first_operand = Link(input1, i * dim, length_x, false);
            second_operand = Link(input2, j * dim, length_y, false);
            operation_nodes.push_back(make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), first_operand, second_operand));
        }
    }
    return createTree(operation_nodes, "Standard tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", x, y);
}

MultiplicationTree StandardTiling::disposeRectangleSquare(int x, int y, Multiplier multiplier)
{
    // TO DO
    return MultiplicationTree();
}

MultiplicationTree StandardTiling::disposeRectangleRectangle(int x, int y, Multiplier multiplier)
{
    // TO DO
    return MultiplicationTree();
}

MultiplicationTree StandardTiling::createTree(vector <shared_ptr<OperationNode>> operation_nodes, string description, int length_x, int length_y)
{
    vector <shared_ptr<OperationNode>> tmp_array;
    shared_ptr<OperationNode> operation_node;
    Link first_operand, second_operand;
    int i;

    while(operation_nodes.size() > 0 && operation_nodes.size() != 1)
    {	
        for(i = 0; i < operation_nodes.size(); i = i + 2)
        {
            if (i + 1 < operation_nodes.size())
            {
                first_operand = Link(operation_nodes[i]);
                second_operand = Link(operation_nodes[i + 1]);
                operation_node = make_shared<OperationNode>(make_shared<Addition>(), first_operand, second_operand);
                tmp_array.push_back(operation_node);
            }
            else
            {
                tmp_array.push_back(operation_nodes[i]);
            }
        }
        operation_nodes.swap(tmp_array);
        tmp_array.clear();
    }
    return MultiplicationTree(operation_nodes[0], description, length_x, length_y);
}


/*    short dim1; 
    short dim2;
    short max;
    short min;
    short index1, index2;
    int nmaxv, nminv, countv, nmaxh, nminh, counth, i, j, k, n, nmaxtmp, lX, lY;
    int w;
    bool match;
    vector <shared_ptr<OperationNode>> operationNodes, tmpArray;
    vector<shared_ptr<InputNode>> inputNodes;
    shared_ptr<OperationNode> operationNode, operationNode2;
    shared_ptr<InputNode> in1, in2;

    dim1 = multiplier.getInputLength1() - 1;
    dim2 = multiplier.getInputLength2() - 1;
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
                index1 = checkExist(true, ((short) (i * max)), (short) lX, inputNodes);
                if(index1 == -1)
                {
                    in1 = make_shared<InputNode>(true, ((short) (i * max)), (short) lX);
                    inputNodes.push_back(in1);
                }
                else
                {
                    in1 = inputNodes[index1];
                }
                index2 = checkExist(false, ((short) (j * max)), (short) lY, inputNodes);
                if(index2 == -1)
                {
                in2 = make_shared<InputNode>(false, ((short) (j * max)), (short) lY);
                inputNodes.push_back(in2);
                }
                else
                {
                    in2 = inputNodes[index2];
                }
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
                    index1 = checkExist(true, ((short) (i * max)), (short) lX, inputNodes);
                    if (index1 == -1)
                    {
                    in1 = make_shared<InputNode>(true, ((short) (i * max)), (short) lX);
                    inputNodes.push_back(in1);
                    }
                    else
                    {
                        in1 = inputNodes[index1];
                    }
                    index2 = checkExist(false, ((short) (j * max)), (short) lY, inputNodes);
                    if (index2 == -1)
                    {
                    in2 = make_shared<InputNode>(false, ((short) (j * max)), (short) lY);
                    inputNodes.push_back(in2);
                    }
                    else
                    {
                        in2 = inputNodes[index2];
                    }
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
                    index1 = checkExist(true, ((short) ((i * max) + (k * min))), (short) lX, inputNodes);
                    if (index1 == -1)
                    {
                    in1 = make_shared<InputNode>(true, ((short) ((i * max) + (k * min))), (short) lX);
                    inputNodes.push_back(in1);
                    }
                    else
                    {
                        in1 = inputNodes[index1];
                    }
                    index2 = checkExist(false, ((short) (j * max)), (short) lY, inputNodes);
                    if (index2 == -1)
                    {
                    in2 = make_shared<InputNode>(false, ((short) (j * max)), (short) lY);
                    inputNodes.push_back(in2);
                    }
                    else
                    {
                        in2 = inputNodes[index2];
                    }
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
                    index1 = checkExist(true, ((short) (j * min)), (short) lX, inputNodes);
                    if (index1 == -1)
                    {
                    in1 = make_shared<InputNode>(true, ((short) (j * min)), (short) lX);
                    inputNodes.push_back(in1);
                    }
                    else
                    {
                        in1 = inputNodes[index1];
                    }
                    index2 = checkExist(false, ((short) (i * max)), (short) lY, inputNodes);
                    if (index2 == -1)
                    {
                    in2 = make_shared<InputNode>(false, ((short) (i * max)), (short) lY);
                    inputNodes.push_back(in2);
                    }
                    else
                    {
                        in2 = inputNodes[index2];
                    }
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
                    index1 = checkExist(true, ((short) (j * max)), (short) lX, inputNodes);
                    if(index1 == -1)
                    {
                    in1 = make_shared<InputNode>(true, ((short) (j * max)), (short) lX);
                    inputNodes.push_back(in1);
                    }
                    else
                    {
                        in1 = inputNodes[index1];
                    }
                    index2 = checkExist(false, ((short) ((i * max) + (k * min))), (short) lY, inputNodes);
                    if(index2 == -1)
                    {
                    in2 = make_shared<InputNode>(false, ((short) ((i * max) + (k * min))), (short) lY);
                    inputNodes.push_back(in2);
                    }
                    else
                    {
                        in2 = inputNodes[index2];
                    }
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

}

short StandardTiling::checkExist(bool firstInput, short start, short length, vector<shared_ptr<InputNode>> inputNodes)
{
    short i;
    for (i = 0; i < inputNodes.size(); i++)
    {
        if (inputNodes[i].get()->isFirstInput() == firstInput && inputNodes[i].get()->getStart() == start && inputNodes[i].get()->getLength() == length)
        {
            return i;
        }
    }
    return -1;
}*/
