#include <iostream>
#include <math.h>
#include "ProposedTiling.h"
#include "../ArithmeticUnit/MultiplicationUnit/LUT/LUT.h"
#include "../Operation/Addition.h"
#include "../Operation/Shift.h"
#include "../Operation/C2.h"
#include "../Operation/And.h"
#include "../Operation/Or.h"
#include "../Operation/Fanout.h"

using namespace std;

ProposedTiling::ProposedTiling(vector<Multiplier> multipliers)
{
    this->multipliers = multipliers;
}

vector<MultiplicationTree> ProposedTiling::dispositions(int lengthX, int lengthY)
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

MultiplicationTree ProposedTiling::disposeHorizontal(int x, int y, Multiplier multiplier)
{
    int dim1; 
    int dim2;
    int max;
    int min;
    int index1, index2;
    int lX;
    int i, j, minv, minh;
    bool match;
    bool sub;
    vector <shared_ptr<OperationNode>> operationNodes, tmpArray;
    shared_ptr<OperationNode> operationNode, operationNodeShift, negator, root;
    shared_ptr<InputNode> in1, in2, in1WSign, in2WSign;
    shared_ptr<MultiplicationUnit> multiplicationUnit, lut;
    Link firstOperand, secondOperand;
    Multiplication *tmp;

    dim1 = multiplier.getInputLength1() - 1;
    dim2 = multiplier.getInputLength2() - 1;
    i = 0;
    j = 0;
    minv = 0;
    minh = 0;
    match = false;
    sub = false;
    multiplicationUnit = make_shared<Multiplier>(multiplier);


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

        in1WSign = make_shared<InputNode>(true, x);
        in2WSign = make_shared<InputNode>(false, y);

        if (isLUTMapped(x, y, multiplier) == true)
        {
            firstOperand = Link(in1WSign, 0, x, true);
            secondOperand = Link(in2WSign, 0, y, true);
            multiplicationUnit = make_shared<LUT>(x, y);
            operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
            operationNode->insertOperandLast(firstOperand);
            operationNode->insertOperandLast(secondOperand);
            return MultiplicationTree(operationNode, "LUT multiplication (Proposed tiling disposition)", x, y);
        }
        else if((min >= x && max >= y) || (max >= x && min >= y))
        {
            firstOperand = Link(in1WSign, 0, x, true);
            secondOperand = Link(in2WSign, 0, y, true);
            operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
            operationNode->insertOperandLast(firstOperand);
            operationNode->insertOperandLast(secondOperand);
            operationNodes.push_back(operationNode);
            return MultiplicationTree(operationNodes[0], "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", x++, y++);
        }
        else //if (match == false)
        {
            x--;
            y--;
            in1 = make_shared<InputNode>(true, x);
            in2 = make_shared<InputNode>(false, y);
            //Parto dall'orizzontale e creo l'array
            if(max < y) 
            {
                // Posiziono il minimo numero di moltiplicatori sulla VERTICALE dall'input di lunghezza minore
                for(; (i * min) + max <= y; i++)
                {
                    if (x < max)
                        lX = x;
                    else
                        lX = max;
                    
                        firstOperand = Link(in1, (j * min), (lX), false);
                    
                    
                        secondOperand = Link(in2, (i * min), min, false);
                        
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    //Tengo conto di quanti moltiplicatori "sdraiati" ho messo sulla verticale
                    minv++;
                }
                // Aggiungo l'ultimo moltiplicatore dal lato maggiore che sforerà o sarà uguale alla dimensione VERTICALE della moltiplicazione da eseguire
                
                    firstOperand = Link(in1, j * min, min, false);
                    
                
                    secondOperand = Link(in2, i * min, y - (i * min), false);
                    
                operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                operationNode->insertOperandLast(firstOperand);
                operationNode->insertOperandLast(secondOperand);
                operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                operationNodes.push_back(operationNodeShift);
                minh++;

                if(max >= x)
                {
                    firstOperand = Link(in1, min, x - min, false);
                    secondOperand = Link(in2, minv * min, y - (minv * min), false);
                    if(isLUTMapped(firstOperand.getLength(), secondOperand.getLength(), multiplier) == true)
                    {
                        lut = make_shared<LUT>(firstOperand.getLength(), secondOperand.getLength());
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(lut));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
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
                        
                            firstOperand = Link(in1, max + ((j - 1) * min), min, false);
                           
                        
                            secondOperand = Link(in2, i * min, max, false);
                            
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                        minh++;
                    }
                    
                // Aggiungo l'ultimo moltiplicatore dal lato minimo che sforerà la dimensione della moltiplicazione da eseguire
                    
                        firstOperand = Link(in1, max + (j - 1) * min, x - max - (j - 1) * min, false);
                        secondOperand = Link(in2, i * min, max, false);
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                // Posiziono il moltiplicatore più estremo
                    i = minv;
                    j = minh;
                    
                        firstOperand = Link(in1, j * min, x - (j * min), false); 
                        secondOperand = Link(in2, max + (i - 1) * min, min - ((i*min) + max - y), false);
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    
                // Posiziono i moltiplicatori rimanenti sulla verticale e sull'orizzontale
                    for(i = minv - 1, j = minh; i > 0; i--)
                    {
                            firstOperand = Link(in1, j * min, x - (j*min), false);
                            secondOperand = Link(in2,  max + ((i - 1) * min), min, false);
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    for(i = minv, j = minh - 1; j > 0; j--)
                    {
                            firstOperand = Link(in1, j * min, min, false);
                            secondOperand = Link(in2, i * min, y - (i * min), false);
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }

                // Verifico che la parte centrale rimanente sia mappabile tramite LUT.
                // Se non lo è allora scarto la soluzione
                    if((minh * min) > max && (minv * min) > max)
                    {
                        firstOperand = Link(in1, max,  (minh * min) - max, false);
                        secondOperand = Link(in2, max, (minv * min) - max, false);
                    }
                    else if ((minh * min) < max && (minv * min) < max)
                    {
                        firstOperand = Link(in1, min, max - min, false);
                        secondOperand = Link(in2, min, max - min, false);
                    }
                    else if ((minv * min) > max && (minh * min) < max)
                    {
                        firstOperand = Link(in1, min, max - min, false);
                        secondOperand = Link(in2, max, (minv * min) - max, false);
                    }
                    else if ((minh * min) > max && (minv * min) < max)
                    {
                        firstOperand = Link(in1, max, (minh * min) - max, false);
                        secondOperand = Link(in2, min, max - min, false);
                    }

                    if(isLUTMapped(firstOperand.getLength(), secondOperand.getLength(), multiplier) == true)
                    {
                        lut = make_shared<LUT>(firstOperand.getLength(), secondOperand.getLength());
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(lut));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
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
        while(operationNodes.size() > 0 && operationNodes.size() != 1)
        {	
            for(i = 0; i < operationNodes.size(); i = i + 2)
            {
                if (i + 1 < operationNodes.size())
                {
                    if (i + 1 == operationNodes.size() - 1 && ((minh * min > max && minv * min < max) || (minh*min < max && minv * min > max)) && operationNodes.size() % 2 == 0 && sub == false)
                    {
                        //Subtraction
                        negator = make_shared<OperationNode>(make_shared<C2>());
                        negator->insertOperandLast(Link(operationNodes[i+1]));
                        operationNodes[i+1] = negator;
                        sub = true;
                    }
                    operationNode = make_shared<OperationNode>(make_shared<Addition>());
                    operationNode->insertOperandLast(Link(operationNodes[i]));
                    operationNode->insertOperandLast(Link(operationNodes[i+1]));
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
        root = addSignedOperation(operationNodes[0], x + 1, y + 1, in1WSign, in2WSign);
        return MultiplicationTree(root, "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ") orizzontale", (int) x + 1, (int) y + 1);
    }
    else    
        return MultiplicationTree();
}

MultiplicationTree ProposedTiling::disposeVertical(int x, int y, Multiplier multiplier)
{
    int dim1; 
    int dim2;
    int max;
    int min;
    int index1, index2;
    int lX, lY;
    int i, j, maxv, maxh, a, b;
    bool sub;
    vector <shared_ptr<OperationNode>> operationNodes, tmpArray;
    shared_ptr<OperationNode> operationNode, operationNodeShift, root;
    shared_ptr<InputNode> in1, in2, in1WSign, in2WSign;
    shared_ptr<MultiplicationUnit> multiplicationUnit, lut;
    Link firstOperand, secondOperand;
    Multiplication *tmp;

    dim1 = multiplier.getInputLength1() - 1;
    dim2 = multiplier.getInputLength2() - 1;
    i = 0;
    j = 0;
    maxv = 0;
    maxh = 0;

    in1WSign = make_shared<InputNode>(true, x);
    in2WSign = make_shared<InputNode>(false, y);

    x--;
    y--;
    multiplicationUnit = make_shared<Multiplier>(multiplier);

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

        in1 = make_shared<InputNode>(true, x);
        in2 = make_shared<InputNode>(false, y);

        //Il match è già stato trovato con la disposizione in orizzontale. È inutile ripetere la soluzione
        if(((min >= x && max >= y) || (max >= x && min >= y)) == false)
        {
            if (max >= y)
            {
                //Se un moltiplicatore in verticale copre l'intera verticale allora cerco di coprire solo l'orizzontale
                if(x > min)
                {
                    firstOperand = Link(in1, 0, min, false);
                    secondOperand = Link(in2, 0, y, false);
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    for(i = 1; min + (i * max) < x; i++)
                    {
                        firstOperand = Link(in1, min + (i * max), max, false);
                        secondOperand = Link(in2, 0, min, false);
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }

                    firstOperand = Link(in1, min + ((i - 1) * max), max - (min + (i * max) - y), false);
                    secondOperand = Link(in2, 0, min, false);
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    firstOperand = Link(in1, min, x - min, false);
                    secondOperand = Link(in2, min, y - min, false);
                    if(isLUTMapped(firstOperand.getLength(), secondOperand.getLength(), multiplier) == true)
                    {
                        lut = make_shared<LUT>(firstOperand.getLength(), secondOperand.getLength());
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(lut));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    else
                        return MultiplicationTree();
                }
            }
            else
            {
                //max < y e faccio la dispsizione verticale
                /*--- x < min ---*/
                if(min > x)
                    lX = x;
                else
                    lX = min;
                for (i = 0; (i * max) + min < y ; i++)
                {
                    firstOperand = Link(in1, 0, lX, false);
                    secondOperand = Link(in2, i * max, max, false);
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    maxv++;
                }
                if(max > x)
                    lX = x;
                else
                    lX = max;
                
                firstOperand = Link(in1, 0, lX, false);
                secondOperand = Link(in2, i * max, min - ((i * max) + min - y), false);
                operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                operationNode->insertOperandLast(firstOperand);
                operationNode->insertOperandLast(secondOperand);
                operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                operationNodes.push_back(operationNodeShift);
                /*--- x < min ---*/

                /*--- x > min && x < max---*/
                if(x > min && x < max) 
                {
                    //Controllo che la parte non coperta sia una LUT
                    firstOperand = Link(in1, 0, x - min, false);
                    secondOperand = Link(in2, 0, i * max, false);
                    if(isLUTMapped(firstOperand.getLength(), secondOperand.getLength(), multiplier) == true)
                    {
                        lut = make_shared<LUT>(firstOperand.getLength(), secondOperand.getLength());
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(lut));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    else
                    {
                        //TODO decidere cosa fare se non è una LUT
                        cout << "La parte da coprire non è una LUT" << endl;
                        return MultiplicationTree();
                    }
                }
                else if (x > max)
                {
                    //cout << "lo provo questo else if?" << endl;
                    i = 0;
                    cout << min + ((i+1) * max) << endl;
                    for(i = 0; min + ((i+1) * max) < x; i++)
                    {
                        //Completo parte superiore della moltiplicazione
                        firstOperand = Link(in1, min + (i * max), max, false);
                        secondOperand = Link(in2, 0, min, false);
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                        maxh++;
                    }
                    //Aggiungo il mancante troncato della parte superiore
                    firstOperand = Link(in1, min + (maxh * max), max - (min + ((maxh + 1) * max) - x), false);
                    secondOperand = Link(in2, 0, min, false);
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    maxh++;

                    for (i = 1; ((i+1) * max) + min < x ; i++)
                    {
                        //Aggiungo i moltiplicatori sdraiati nella parte inferiore della moltiplicazione
                        firstOperand = Link(in1, i * max, max, false);
                        secondOperand = Link(in2, maxv * max, min - ((maxv * max) + min - y), false);
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    for(i = maxv-1, j = 0; i > 0; i--, j++)
                    {
                        //Aggiungo i moltiplicatori completi sul lato sinistro della moltiplicazione
                        firstOperand = Link(in1, maxh * max, min - (min + ((maxh + 1) * max) - x), false);
                        secondOperand = Link(in2, min + (j * max), max, false);
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    //Aggiungo l'ultimo moltiplicatore troncato sia a sinistra sia in basso
                    firstOperand = Link(in1, maxh * max, min - (min + ((maxh) * max) - x), false);
                    secondOperand = Link(in2, min + (j * max), max - ((maxv * max) + min - y), false);
                    operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
                    operationNode->insertOperandLast(firstOperand);
                    operationNode->insertOperandLast(secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    //Verifico che la parte rimanente sia mappabile su una LUT
                    firstOperand = Link(in1, min, maxh * max - min, false);
                    secondOperand = Link(in2, min, (maxv * max) - min, false);
                    if(isLUTMapped(firstOperand.getLength(), secondOperand.getLength(), multiplier) == true)
                    {
                        lut = make_shared<LUT>(firstOperand.getLength(), secondOperand.getLength());
                        operationNode = make_shared<OperationNode>(make_shared<Multiplication>(lut));
                        operationNode->insertOperandLast(firstOperand);
                        operationNode->insertOperandLast(secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    else
                    {
                        //TODO decidere cosa fare se non è una LUT
                        cout << "La parte da coprire non è una LUT in verticale" << endl;
                        return MultiplicationTree();
                    }
                }
            }
            // Creo l'albero di somme di moltiplicazioni
            while(operationNodes.size() > 0 && operationNodes.size() != 1)
            {   
                for(i = 0; i < operationNodes.size(); i = i + 2)
                {
                    if (i + 1 < operationNodes.size())
                    {
                        operationNode = make_shared<OperationNode>(make_shared<Addition>());
                        operationNode->insertOperandLast(Link(operationNodes[i]));
                        operationNode->insertOperandLast(Link(operationNodes[i+1]));
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
            root = addSignedOperation(operationNodes[0], x + 1, y + 1, in1WSign, in2WSign);
            return MultiplicationTree(root, "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ") verticale", (int) x + 1, (int) y + 1);
        }
        else
            return MultiplicationTree();
    }
    else
        return MultiplicationTree();
}

shared_ptr<OperationNode> ProposedTiling::makeShift(Link firstOperand, Link secondOperand, shared_ptr<OperationNode> operationNode)
{
    shared_ptr<OperationNode> operationNodeShift;
    if(firstOperand.getStart() + secondOperand.getStart() > 0)
    {
        operationNodeShift = make_shared<OperationNode>(make_shared<Shift>(firstOperand.getStart() + secondOperand.getStart()));
        operationNodeShift->insertOperandLast(Link(operationNode));
        return operationNodeShift;
    }
    else
    {
        return operationNode;
    }
}

bool ProposedTiling::isLUTMapped(int x, int y, Multiplier multiplier)
{
    int min_input, max_input, min_threshold, max_threshold;
    bool result;

    if(multiplier.getInputThreshold1() > multiplier.getInputThreshold2())
    {
        min_threshold = multiplier.getInputThreshold2();
        max_threshold = multiplier.getInputThreshold1();
    }
    else
    {
        min_threshold = multiplier.getInputThreshold1();
        max_threshold = multiplier.getInputThreshold2();
    }
    if(x > y)
    {
        min_input = y;
        max_input = x;
    }
    else
    {
        min_input = x;
        max_input = y;
    }
    if(min_input < min_threshold || max_input < max_threshold)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

shared_ptr<OperationNode> ProposedTiling::addSignedOperation(shared_ptr<OperationNode> root, int x, int y, shared_ptr<InputNode> input1, shared_ptr<InputNode> input2)
{
    shared_ptr<OperationNode> operation1, operation2, operation3;
    Link operand1, operand2;

    // First of all the positive part
    // If the sign of x and y is 1, then i have a 1 in the (lengthX + lengthY - 2) position
    operation1 = make_shared<OperationNode>(make_shared<And>());
    operand1 = Link(input1, x - 1, 1);
    operand2 = Link(input2, y - 1, 1);
    operation1->insertOperandLast(operand1);
    operation1->insertOperandLast(operand2);
    operation2 = make_shared<OperationNode>(make_shared<Shift>(x + y - 2), x + y);
    operand1 = Link(operation1);
    operand1.setSignIncluded(false);
    operation2->insertOperandLast(operand1);
    // Then the negative part: sign of x must be fanouted by length y and then anded with y. Finally shifted of length of x and then complemented.
    operation1 = make_shared<OperationNode>(make_shared<Fanout>(y - 1));
    operand1 = Link(input1, x - 1, 1);
    operation1->insertOperandLast(operand1);
    operation3 = make_shared<OperationNode>(make_shared<And>());
    operand1 = Link(operation1);
    operand2 = Link(input2, 0, y - 1, false);
    operation3->insertOperandLast(operand1);
    operation3->insertOperandLast(operand2);
    operation1 = make_shared<OperationNode>(make_shared<Shift>(x - 1));
    operand1 = Link(operation3);
    operand1.setSignIncluded(false);
    operation1->insertOperandLast(operand1);
    operation3 = make_shared<OperationNode>(make_shared<C2>());
    operand1 = Link(operation1);
    operation3->insertOperandLast(operand1);
    // This is summed with the positive part
    operation1 = make_shared<OperationNode>(make_shared<Addition>());
    operand1 = Link(operation2);
    operand2 = Link(operation3);
    operation1->insertOperandLast(operand1);
    operation1->insertOperandLast(operand2);
    // The last negative part is made by the past negative part with x and y inverted
    operation2 = make_shared<OperationNode>(make_shared<Fanout>(x - 1));
    operand1 = Link(input2, y - 1, 1);
    operation2->insertOperandLast(operand1);
    operation3 = make_shared<OperationNode>(make_shared<And>());
    operand1 = Link(operation2);
    operand2 = Link(input1, 0, x - 1, false);
    operation3->insertOperandLast(operand1);
    operation3->insertOperandLast(operand2);
    operation2 = make_shared<OperationNode>(make_shared<Shift>(y - 1));
    operand1 = Link(operation3);
    operand1.setSignIncluded(false);
    operation2->insertOperandLast(operand1);
    operation3 = make_shared<OperationNode>(make_shared<C2>());
    operand1 = Link(operation2);
    operation3->insertOperandLast(operand1);
    // This part is summed to the past part
    operation2 = make_shared<OperationNode>(make_shared<Addition>());
    operand1 = Link(operation1);
    operand2 = Link(operation3);
    operation2->insertOperandLast(operand1);
    operation2->insertOperandLast(operand2);
    // Finally summed with root
    operation1 = make_shared<OperationNode>(make_shared<Addition>());
    operand1 = Link(root);
    operand2 = Link(operation2);
    operation1->insertOperandLast(operand1);
    operation1->insertOperandLast(operand2);
    return operation1;
}
