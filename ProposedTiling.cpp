#include <iostream>
#include <math.h>
#include "ProposedTiling.h"
#include "InputNode.h"
#include "SubMultiplication.h"
#include "Subtraction.h"
#include "Addition.h"
#include "ShiftNode.h"

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
    int i, j, minv, minh;
    bool match;
    bool sub;
    vector <shared_ptr<Node>> operationNodes, tmpArray;
    vector<shared_ptr<InputNode>> inputNodes;
    shared_ptr<OperationNode> operationNode;
    shared_ptr<ShiftNode> operationNodeShift;
    shared_ptr<InputNode> in1, in2;
    Link firstOperand, secondOperand;
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

        in1 = make_shared<InputNode>(true, x);
        in2 = make_shared<InputNode>(false, y);

        if((min >= x && max >= y) || (max >= x && min >= y))
        {
            firstOperand = Link(in1, (short) 0, x, false);
            secondOperand = Link(in2, (short) 0, y, false);
            operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
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
                    
                        firstOperand = Link(in1, ((short) j * min), ((short) lX), false);
                    
                    
                        secondOperand = Link(in2, ((short) i * min), ((short) min), false);
                        
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    //Tengo conto di quanti moltiplicatori "sdraiati" ho messo sulla verticale
                    minv++;
                }
                // Aggiungo l'ultimo moltiplicatore dal lato maggiore che sforerà o sarà uguale alla dimensione VERTICALE della moltiplicazione da eseguire
                
                    firstOperand = Link(in1, ((short) j * min), ((short) min), false);
                    
                
                    secondOperand = Link(in2, ((short) i * min), ((short) y - (i * min)), false);
                    
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                operationNodes.push_back(operationNodeShift);
                minh++;

                if(max >= x)
                {
                    firstOperand = Link(in1, min, x - min, false);
                    secondOperand = Link(in2, minv * min, y - (minv * min), false);
                    if(firstOperand.getLength() <= multiplier.getMinInput1() && secondOperand.getLength() <= multiplier.getMinInput2())
                    {
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(), firstOperand, secondOperand);
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
                        
                            firstOperand = Link(in1, ((short) max + ((j-1)*min)), (short) min, false);
                           
                        
                            secondOperand = Link(in2, ((short) i * min), (short) max, false);
                            
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                        minh++;
                    }
                    
                // Aggiungo l'ultimo moltiplicatore dal lato minimo che sforerà la dimensione della moltiplicazione da eseguire
                    
                        firstOperand = Link(in1, ((short) max + (j-1) * min), ((short) x - max - (j-1)*min), false);
                        secondOperand = Link(in2, ((short) i*min), ((short) max), false);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                // Posiziono il moltiplicatore più estremo
                    i = minv;
                    j = minh;
                    
                        firstOperand = Link(in1, ((short) j * min), ((short) x - (j*min)), false); 
                        secondOperand = Link(in2, ((short) max + ((i-1)*min)), ((short) min - ((i*min) + max - y)), false);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    
                // Posiziono i moltiplicatori rimanenti sulla verticale e sull'orizzontale
                    for(i = minv - 1, j = minh; i > 0; i--)
                    {
                            firstOperand = Link(in1, ((short) j * min), (short) x - (j*min), false);
                            secondOperand = Link(in2, ((short) max + ((i-1)*min)), ((short) min), false);
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    for(i = minv, j = minh - 1; j > 0; j--)
                    {
                            firstOperand = Link(in1, ((short) j * min), ((short) min), false);
                            secondOperand = Link(in2, ((short) i * min), ((short) y - (i * min)), false);
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }

                // Verifico che la parte centrale rimanente sia mappabile tramite LUT.
                // Se non lo è allora scarto la soluzione
                    if((minh * min) > max && (minv * min) > max)
                    {
                        firstOperand = Link(in1, ((short) max), ((short) (minh*min) - max), false);
                        secondOperand = Link(in2, ((short) max), ((short) (minv*min) - max), false);
                    }
                    else if ((minh * min) < max && (minv * min) < max)
                    {
                        firstOperand = Link(in1, ((short) min), ((short) (max - min)), false);
                        secondOperand = Link(in2, ((short) min), ((short) (max - min)), false);
                    }
                    else if ((minv * min) > max && (minh * min) < max)
                    {
                        firstOperand = Link(in1, (short) min, (short) max - min, false);
                        secondOperand = Link(in2, (short) max, (short) (minv * min) - max, false);
                    }
                    else if ((minh * min) > max && (minv * min) < max)
                    {
                        firstOperand = Link(in1, (short) max, (short) (minh * min) - max, false);
                        secondOperand = Link(in2, (short) min, (short) max - min, false);
                    }

                    if(firstOperand.getLength() < multiplier.getMinInput1() && secondOperand.getLength() < multiplier.getMinInput2())
                    {
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(), firstOperand, secondOperand);
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
                        operationNode = make_shared<OperationNode>(make_shared<Subtraction>());
                        sub = true;
                    }
                    else
                    {
                        operationNode = make_shared<OperationNode>(make_shared<Addition>());
                    }
                    operationNode->setFirstOperand(Link(operationNodes[i]));
                    operationNode->setSecondOperand(Link(operationNodes[i+1]));
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

MultiplicationTree ProposedTiling::disposeVertical(short x, short y, Multiplier multiplier)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    short index1, index2;
    short lX, lY;
    int i, j, maxv, maxh, a, b;
    bool sub;
    vector <shared_ptr<Node>> operationNodes, tmpArray;
    //vector<shared_ptr<InputNode>> inputNodes;
    shared_ptr<OperationNode> operationNode;
    shared_ptr<ShiftNode> operationNodeShift;
    shared_ptr<InputNode> in1, in2;
    Link firstOperand, secondOperand;
    SubMultiplication *tmp;

    dim1 = multiplier.getInputLength1() - 1;
    dim2 = multiplier.getInputLength2() - 1;
    i = 0;
    j = 0;
    maxv = 0;
    maxh = 0;
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
                    firstOperand = Link(in1, (short) 0, min, false);
                    secondOperand = Link(in2, (short) 0, y, false);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    for(i = 1; min + (i * max) < x; i++)
                    {
                        firstOperand = Link(in1, (short) min + (i * max), (short) max, false);
                        secondOperand = Link(in2, (short) 0, min, false);
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    firstOperand = Link(in1, (short) min + ((i-1) * max), (short) max - (min + (i * max) - y), false);
                    secondOperand = Link(in2, (short) 0, min, false);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    firstOperand = Link(in1, min, x - min, false);
                    secondOperand = Link(in2, min, y - min, false);
                    if(firstOperand.getLength() < multiplier.getMinInput1() && secondOperand.getLength() < multiplier.getMinInput2())
                    {
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(), firstOperand, secondOperand);
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
                    firstOperand = Link(in1, (short) 0, lX, false);
                    secondOperand = Link(in2, (short) i * max, max, false);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    maxv++;
                }
                if(max > x)
                    lX = x;
                else
                    lX = max;
                
                firstOperand = Link(in1, (short) 0, lX, false);
                secondOperand = Link(in2, (short) (i * max), (short) min - ((i * max) + min - y), false);
                operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                operationNodes.push_back(operationNodeShift);
                /*--- x < min ---*/

                /*--- x > min && x < max---*/
                if(x > min && x < max) 
                {
                    //Controllo che la parte non coperta sia una LUT
                    firstOperand = Link(in1, (short) 0, (short) x - min, false);
                    secondOperand = Link(in2, (short) 0, (short) i * max, false);
                    if(firstOperand.getLength() < multiplier.getMinInput1() && secondOperand.getLength() < multiplier.getMinInput2())
                    {
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(), firstOperand, secondOperand);
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
                        firstOperand = Link(in1, min + (i * max), (short) max, false);
                        secondOperand = Link(in2, (short) 0, min, false);
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                        maxh++;
                    }
                    //Aggiungo il mancante troncato della parte superiore
                    firstOperand = Link(in1, (short) min + (maxh * max), (short) max - (min + ((maxh + 1) * max) - x), false);
                    secondOperand = Link(in2, (short) 0, min, false);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);
                    maxh++;

                    for (i = 1; ((i+1) * max) + min < x ; i++)
                    {
                        //Aggiungo i moltiplicatori sdraiati nella parte inferiore della moltiplicazione
                        firstOperand = Link(in1, (short) i * max, max, false);
                        secondOperand = Link(in2, (short) maxv * max, (short) min - ((maxv * max) + min - y), false);
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    for(i = maxv-1, j = 0; i > 0; i--, j++)
                    {
                        //Aggiungo i moltiplicatori completi sul lato sinistro della moltiplicazione
                        firstOperand = Link(in1, (short) (maxh) * max, (short) min - (min + ((maxh + 1) * max) - x), false);
                        secondOperand = Link(in2, (short) min + (j * max), max, false);
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                        operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                        operationNodes.push_back(operationNodeShift);
                    }
                    //Aggiungo l'ultimo moltiplicatore troncato sia a sinistra sia in basso
                    firstOperand = Link(in1, (short) (maxh) * max, (short) min - (min + ((maxh) * max) - x), false);
                    secondOperand = Link(in2, (short) min + (j * max), (short) max - ((maxv * max) + min - y), false);
                    operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(multiplier), firstOperand, secondOperand);
                    operationNodeShift = makeShift(firstOperand, secondOperand, operationNode);
                    operationNodes.push_back(operationNodeShift);

                    //Verifico che la parte rimanente sia mappabile su una LUT
                    firstOperand = Link(in1, min, (short) ((maxh) * max) - min, false);
                    secondOperand = Link(in2, min, (short) (maxv * max) - min, false);
                    if(firstOperand.getLength() < multiplier.getMinInput1() && secondOperand.getLength() < multiplier.getMinInput2())
                    {
                        operationNode = make_shared<OperationNode>(make_shared<SubMultiplication>(), firstOperand, secondOperand);
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
                        operationNode->setFirstOperand(operationNodes[i]);
                        operationNode->setSecondOperand(operationNodes[i+1]);
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

shared_ptr<Node> ProposedTiling::makeShift(Link firstOperand, Link secondOperand, shared_ptr<OperationNode> operationNode)
{
    shared_ptr<ShiftNode> operationNodeShift;
    if(firstOperand.getStart() + secondOperand.getStart() > 0)
    {
        operationNodeShift = make_shared<ShiftNode>(Link(operationNode), firstOperand.getStart() + secondOperand.getStart());
        return operationNodeShift;
    }
    else
    {
        return operationNode;
    }
}

/*
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
*/