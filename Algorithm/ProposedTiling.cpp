#include <iostream>
#include <math.h>
#include "ProposedTiling.h"
#include "../Node/InputNode.h"
#include "../ArithmeticUnit/MultiplicationUnit/LUT/LUT.h"
#include "../Operation/Addition.h"
#include "../Operation/Shift.h"

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
    shared_ptr<OperationNode> operationNode, operationNodeShift;
    shared_ptr<InputNode> in1, in2;
    shared_ptr<MultiplicationUnit> multiplicationUnit, lut;
    Link firstOperand, secondOperand;
    Multiplication *tmp;

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

        if((min >= x && max >= y) || (max >= x && min >= y))
        {
            firstOperand = Link(in1, 0, x, false);
            secondOperand = Link(in2, 0, y, false);
            operationNode = make_shared<OperationNode>(make_shared<Multiplication>(multiplicationUnit));
            operationNode->insertOperandLast(firstOperand);
            operationNode->insertOperandLast(secondOperand);
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
                    if(firstOperand.getLength() + secondOperand.getLength() <= multiplier.getOutputThreshold())
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

                    if(firstOperand.getLength() + secondOperand.getLength() <= multiplier.getOutputThreshold())
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
                        //TODO Subtraction
                        operationNode = make_shared<OperationNode>(make_shared<Addition>());
                        sub = true;
                    }
                    else
                    {
                        operationNode = make_shared<OperationNode>(make_shared<Addition>());
                    }
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
        
        return MultiplicationTree(operationNodes[0], "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ") orizzontale", (int) x + 1, (int) y + 1);
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
    shared_ptr<OperationNode> operationNode, operationNodeShift;
    shared_ptr<InputNode> in1, in2;
    shared_ptr<MultiplicationUnit> multiplicationUnit, lut;
    Link firstOperand, secondOperand;
    Multiplication *tmp;

    dim1 = multiplier.getInputLength1() - 1;
    dim2 = multiplier.getInputLength2() - 1;
    i = 0;
    j = 0;
    maxv = 0;
    maxh = 0;
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
                    if(firstOperand.getLength() + secondOperand.getLength() <= multiplier.getOutputThreshold())
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
                    if(firstOperand.getLength() + secondOperand.getLength() <= multiplier.getOutputThreshold())
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
                    if(firstOperand.getLength() + secondOperand.getLength() <= multiplier.getOutputThreshold())
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
            
            return MultiplicationTree(operationNodes[0], "Proposed tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ") verticale", (int) x + 1, (int) y + 1);
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