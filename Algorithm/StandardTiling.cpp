#include <iostream>
#include <math.h>
#include "StandardTiling.h"
#include "../Operation/Multiplication.h"
#include "../Operation/Shift.h"
#include "../ArithmeticUnit/MultiplicationUnit/LUT/LUT.h"
#include "../Operation/Addition.h"
#include "../Operation/And.h"
#include "../Operation/Or.h"
#include "../Operation/C2.h"
#include "../Operation/Fanout.h"

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
    shared_ptr<MultiplicationUnit> multiplication_unit;
    shared_ptr<InputNode> input1, input2;
    shared_ptr<OperationNode> root;

    // Pre-checks
    // Both lengths must be greater than 1, otherwise there aren't enough bit for the multiplication.
    if(x <= 1 || y <= 1)
    {
        return MultiplicationTree();
    }
    if(isLUTMapped(x, y, multiplier) == true)
    {
        input1 = make_shared<InputNode>(true, x);
        input2 = make_shared<InputNode>(false, y);
        first_operand = Link(input1, 0, x, true);
        second_operand = Link(input2, 0, y, true);
        multiplication_unit = make_shared<LUT>(x, y);
        root = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
        root->insertOperandLast(first_operand);
        root->insertOperandLast(second_operand);
        return MultiplicationTree(root, "LUT multiplication (Standard tiling disposition)", x, y);
    }
    else
    {
        //Checks if can be done with just a multiplier
        if((multiplier.getInputLength1() >= x && multiplier.getInputLength2() >= y) ||\
           (multiplier.getInputLength1() >= y && multiplier.getInputLength2() >= x))
        {
            input1 = make_shared<InputNode>(true, x);
            input2 = make_shared<InputNode>(false, y);
            first_operand = Link(input1, 0, x, true);
            second_operand = Link(input2, 0, y, true);
            multiplication_unit = make_shared<Multiplier>(multiplier);
            root = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
            root->insertOperandLast(first_operand);
            root->insertOperandLast(second_operand);
            return MultiplicationTree(root, "Standard tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", x, y);
        }
    }
    // For simplicity we dived the dispose function in 3 function: one for a square multiplier, one for a rectangular multiplier
    // in a square multiplication and one for a rectangular multiplier in a rectangular multiplication. In this way there will be
    // more code but simple and modifiable in an easy way.
    if(multiplier.getInputLength1() == multiplier.getInputLength2())
    {
        return disposeSquare(x, y, multiplier);
    }
    else
    {
        return disposeRectangle(x, y, multiplier);
    }
}

MultiplicationTree StandardTiling::disposeSquare(int x, int y, Multiplier multiplier)
{
    int i, j, dim, length_x, length_y;
    shared_ptr<InputNode> input1, input2;
    shared_ptr<MultiplicationUnit> multiplication_unit;
    Link first_operand, second_operand, shifted_operand;
    shared_ptr<OperationNode> operation_node, shift_node, root;
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
            if(isLUTMapped(length_x + 1, length_y + 1, multiplier))
            {
                multiplication_unit = make_shared<LUT>(length_x + 1, length_y + 1);
            }
            else
            {
                multiplication_unit = make_shared<Multiplier>(multiplier);
            }
            operation_node = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
            operation_node->insertOperandLast(first_operand);
            operation_node->insertOperandLast(second_operand);
            if((i * dim) + (j * dim) > 0)
            {
                shifted_operand = Link(operation_node);
                shift_node = make_shared<OperationNode>(make_shared<Shift>((i * dim) + (j * dim)));
                shift_node->insertOperandLast(shifted_operand);
                operation_node = shift_node;
            }
            operation_nodes.push_back(operation_node);
        }
    }
    root = createTree(operation_nodes);
    root = addSignedOperation(root, x, y, input1, input2);
    return MultiplicationTree(root, "Standard tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", x, y);
}

MultiplicationTree StandardTiling::disposeRectangle(int x, int y, Multiplier multiplier)
{
    int min_dim, max_dim, nmax, nmin, nbit, nmax2, nmin2, nbit2, i, j, axe_length, length_x, length_y;
    shared_ptr<InputNode> input1, input2;
    bool inverted;
    shared_ptr<MultiplicationUnit> multiplication_unit;
    Link first_operand, second_operand, shifted_operand;
    shared_ptr<OperationNode> operation_node, shift_node, root;
    vector <shared_ptr<OperationNode>> operation_nodes;

    x--;
    y--;
    input1 = make_shared<InputNode>(true, x);
    input2 = make_shared<InputNode>(false, y);
    if(multiplier.getInputLength1() > multiplier.getInputLength2())
    {
        max_dim = multiplier.getInputLength1();
        min_dim = multiplier.getInputLength2();
    }
    else
    {
        min_dim = multiplier.getInputLength1();
        max_dim = multiplier.getInputLength2();
    }
    nbit = disposeOnAxe(&nmax, &nmin, x, multiplier);
    if(x != y)
    {
        nbit2 = disposeOnAxe(&nmax2, &nmin2, y, multiplier);
        inverted = false;
        if(nbit > 0)
        {
            if(nbit2 == 0 || nbit2 < nbit)
            {
                inverted = true;
                nmax = nmax2;
                nmin = nmin2;
            }
        }
        else if(nbit < 0)
        {
            if(nbit2 >= 0 || nbit2 > nbit)
            {
                inverted = true;
                nmax = nmax2;
                nmin = nmin2;
            }
        }
    }
    if(inverted == true)
    {
        std::cout << "Inverted" << endl;
    }
    std::cout << "nmax = " << nmax << endl;
    std::cout << "nmin = " << nmin << endl;
    // Disposing the multiplications. I know how many multiplier and in which way they are disposed along an axe.
    // Filling the other axe with the same multiplier in the same disposition.
    if(inverted == true)
    {
        axe_length = x;
    }
    else
    {
        axe_length = y;
    }
    for(i = 0; i < nmax; i++)
    {
        if(i == nmax - 1 && nmin == 0)
        {
            length_x = max_dim;
        }
        else
        {
            length_x = axe_length - (max_dim * i);
        }
        for(j = 0; j * min_dim < axe_length; j++)
        {
            if((j + 1) * min_dim > axe_length)
            {
                length_y = min_dim - ((j + 1) * min_dim) + axe_length;
            }
            else
            {
                length_y = min_dim;
            }
            if(inverted == true)
            {
                second_operand = Link(input2, i * max_dim, length_x, false);
                first_operand = Link(input1, j * min_dim, length_y, false);
            }
            else
            {
                first_operand = Link(input1, i * max_dim, length_x, false);
                second_operand = Link(input2, j * min_dim, length_y, false);
            }
            if(isLUTMapped(length_x + 1, length_y + 1, multiplier))
            {
                multiplication_unit = make_shared<LUT>(length_x + 1, length_y + 1);
            }
            else
            {
                multiplication_unit = make_shared<Multiplier>(multiplier);
            }
            operation_node = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
            operation_node->insertOperandLast(first_operand);
            operation_node->insertOperandLast(second_operand);
            if((i * max_dim) + (j * min_dim) > 0)
            {
                shifted_operand = Link(operation_node);
                shift_node = make_shared<OperationNode>(make_shared<Shift>((i * max_dim) + (j * min_dim)));
                shift_node->insertOperandLast(shifted_operand);
                operation_node = shift_node;
            }
            operation_nodes.push_back(operation_node);
        }
    }
    for(i = 0; i < nmin; i++)
    {
        if(i == nmin - 1)
        {
            length_x = min_dim;
        }
        else
        {
            length_x = axe_length - (min_dim * i);
        }
        for(j = 0; j * max_dim < axe_length; j++)
        {
            if((j + 1) * max_dim > axe_length)
            {
                length_y = max_dim - ((j + 1) * max_dim) + axe_length;
            }
            else
            {
                length_y = max_dim;
            }
            if(inverted == true)
            {
                second_operand = Link(input2, i * min_dim, length_x, false);
                first_operand = Link(input1, j * max_dim, length_y, false);
            }
            else
            {
                first_operand = Link(input1, i * min_dim, length_x, false);
                second_operand = Link(input2, j * max_dim, length_y, false);
            }
            if(isLUTMapped(length_x + 1, length_y + 1, multiplier))
            {
                multiplication_unit = make_shared<LUT>(length_x + 1, length_y + 1);
            }
            else
            {
                multiplication_unit = make_shared<Multiplier>(multiplier);
            }
            operation_node = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
            operation_node->insertOperandLast(first_operand);
            operation_node->insertOperandLast(second_operand);
            if((nmax * max_dim) + (i * min_dim) + (j * max_dim) > 0)
            {
                shifted_operand = Link(operation_node);
                shift_node = make_shared<OperationNode>(make_shared<Shift>((nmax * max_dim) + (i * min_dim) + (j * max_dim)));
                shift_node->insertOperandLast(shifted_operand);
                operation_node = shift_node;
            }
            operation_nodes.push_back(operation_node);
        }
    }
    root = createTree(operation_nodes);
    root = addSignedOperation(root, x, y, input1, input2);
    return MultiplicationTree(root, "Standard tiling (" + to_string(multiplier.getInputLength1()) + "x" + to_string(multiplier.getInputLength2()) + ")", x, y);
}

shared_ptr<OperationNode> StandardTiling::createTree(vector <shared_ptr<OperationNode>> operation_nodes)
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
                operation_node = make_shared<OperationNode>(make_shared<Addition>());
                operation_node->insertOperandLast(first_operand);
                operation_node->insertOperandLast(second_operand);
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
    return operation_nodes[0];
}

shared_ptr<OperationNode> StandardTiling::addSignedOperation(shared_ptr<OperationNode> root, int x, int y, shared_ptr<InputNode> input1, shared_ptr<InputNode> input2)
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

bool StandardTiling::isLUTMapped(int x, int y, Multiplier multiplier)
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

int StandardTiling::disposeOnAxe(int *nmax, int *nmin, int axe_length, Multiplier multiplier)
{
    int i, j, min_dim, max_dim, current_bit, nbit;

    nbit = -1;
    if(multiplier.getInputLength1() > multiplier.getInputLength2())
    {
        max_dim = multiplier.getInputLength1();
        min_dim = multiplier.getInputLength2();
    }
    else
    {
        min_dim = multiplier.getInputLength1();
        max_dim = multiplier.getInputLength2();
    }
    // Trying to figure out the best disposition of rectangular multiplier
    // Firstly tried to use only multipliers. Retrieve the disposition with the minimum number of bit that exceed
    // over the axe length.
    for(i = 0; i * max_dim < axe_length && nbit != 0; i++)
    {
        for(j = 0; (i * max_dim) + (j * min_dim) < axe_length && nbit != 0; j++);
        if(j > 0)
        {
            if(isLUTMapped(max_dim + 1, axe_length - ((i * max_dim) + ((j - 1) * min_dim)) + 1, multiplier) == false)
            {
                current_bit = (((i * max_dim) + (j * min_dim)) - axe_length) * max_dim;
                if(nbit < 0 || (nbit >= 0 && current_bit < nbit))
                {
                    nbit = current_bit;
                    *nmax = i;
                    *nmin = j;
                }
            }
        }
    }
    if(j == 0 && nbit != 0)
    {
        if(isLUTMapped(min_dim + 1, axe_length - ((i - 1) * max_dim) + 1, multiplier) == false)
        {
            current_bit = ((i * max_dim) - axe_length) * max_dim;
            if(nbit < 0 || (nbit >= 0 && current_bit < nbit))
            {
                nbit = current_bit;
                *nmax = i;
                *nmin = 0;
            }
        }
    }
    // If nbit = -1 it means that i didn't found a solution with multipliers, so i need to minimize the number og
    // LUT needed.
    if(nbit == -1)
    {
        nbit = 1;
        for(i = 0; i * max_dim < axe_length && nbit != 0; i++)
        {
            for(j = 0; (i * max_dim) + (j * min_dim) < axe_length && nbit != 0; j++);
            if(j > 0)
            {
                if(isLUTMapped(max_dim + 1, axe_length - ((i * max_dim) + ((j - 1) * min_dim)) + 1, multiplier) == true)
                {
                    current_bit = (((i * max_dim) + (j * min_dim)) - axe_length) * max_dim;
                    current_bit = -current_bit;
                    if(nbit > 0 || (nbit < 0 && current_bit > nbit))
                    {
                        nbit = current_bit;
                        *nmax = i;
                        *nmin = j;
                    }
                }
            }
        }
        if(j == 0 && nbit != 0)
        {
            if(isLUTMapped(min_dim + 1, axe_length - ((i - 1) * max_dim) + 1, multiplier) == true)
            {
                current_bit = ((i * max_dim) - axe_length) * max_dim;
                current_bit = -current_bit;
                if(nbit > 0 || (nbit < 0 && current_bit > nbit))
                {
                    nbit = current_bit;
                    *nmax = i;
                    *nmin = 0;
                }
            }
        }
    }
    return nbit;
}

















