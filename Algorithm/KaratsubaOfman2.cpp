#include <math.h>
#include <iostream>
#include <vector>
#include <memory>
#include "KaratsubaOfman2.h"
#include "StandardTiling.h"
#include "ProposedTiling.h"

using namespace std;


/*****************************************************************************/
/* Constructor that accepts the multipliers available.                       */
/*****************************************************************************/

KaratsubaOfman2::KaratsubaOfman2(vector<Multiplier> multipliers)
{
    this->multipliers = multipliers;
    this->sign_operations_included = true;
}

KaratsubaOfman2::KaratsubaOfman2(vector<Multiplier> multipliers, bool sign_operations_included)
{
    this->multipliers = multipliers;
    this->sign_operations_included = sign_operations_included;
}

bool KaratsubaOfman2::isSignOperationsIncluded()
{
    return this->sign_operations_included;
}

void KaratsubaOfman2::setSignOperationsIncluded(bool sign_operations_included)
{
    this->sign_operations_included = sign_operations_included;
}

/*****************************************************************************/
/* Method that provides all the dispositions available.                      */
/*****************************************************************************/

vector<MultiplicationTree> KaratsubaOfman2::dispositions(int x, int y)
{
    vector<MultiplicationTree> multiplication_trees, returned_trees;
    int i, j;
    MultiplicationTree tmp;

    // Pre-Checks
    // X must be equal to y
    if(x != y)
    {
        return multiplication_trees;
    }
    // Both lengths must be greater than 1, otherwise there aren't enough bit for the multiplication.
    if(x <= 1 || y <= 1)
    {
        return multiplication_trees;
    }
    // Getting dispositions
    this->LUT_solution = false;
    for(i = 0; i < multipliers.size(); i++)
    {
        returned_trees = dispose (x, y, multipliers[i]);
        for(j = 0; j < returned_trees.size(); j++)
        {
            if(returned_trees[j].getRoot() != nullptr)
            {
                multiplication_trees.push_back(returned_trees[j]);
            }
        }
        returned_trees.clear();
    }
    return multiplication_trees;
}

/*****************************************************************************/
/* Method that tries to create a disposition given two input lengths and a   */
/* multiplier.                                                               */
/*****************************************************************************/

vector<MultiplicationTree> KaratsubaOfman2::dispose(int x, int y, Multiplier multiplier)
{
    vector<MultiplicationTree> dispositions;
    int min_dim, i;

    // First of all, pre checks
    // Checking if the multiplication can be mapped in one LUT
    if(Multiplier::isLUTMapped(x, y, multiplier) == true)
    {
        dispositions.push_back(MultiplicationTree());
        return dispositions;
    }
    else
    {
        //Checking if can be done with just a multiplier
        if((multiplier.getInputLength1() >= x && multiplier.getInputLength2() >= y) ||\
           (multiplier.getInputLength1() >= y && multiplier.getInputLength2() >= x))
        {
            dispositions.push_back(MultiplicationTree());
            return dispositions;
        }
    }
    // We don't need a squared multiplier, just considering the minimum side of the multiplier
    if(multiplier.getInputLength1() > multiplier.getInputLength2())
    {
        min_dim = multiplier.getInputLength2();
    }
    else
    {
        min_dim = multiplier.getInputLength1();
    }
    // Checking if it can be splitted in two parts in which each part is covered just by a multiplier
    // If it is, then call not_recursive disposition, otherwise call recursive_disposition
    // Each part has to be smaller than the greatest input divided by two
    if((min_dim * 2) - 1 >= x)
    {
        dispositions.push_back(notRecursiveDisposition(x, y, multiplier));
        return dispositions;
    }
    else
    {

        dispositions = recursiveDisposition(x, y, multiplier);
        return dispositions;
    }
}

MultiplicationTree KaratsubaOfman2::notRecursiveDisposition(int x, int y, Multiplier multiplier)
{
    int part0, part1;
    shared_ptr<InputNode> input1, input2;
    shared_ptr<OperationNode> x0y0, x1y1, dx, dy, dxdy, operation1, operation2, operation3, root;
    Link first_operand, second_operand, first_operand2, second_operand2;
    shared_ptr<MultiplicationUnit> multiplication_unit;

    // Preparings lengths
    part1 = (x - 1) / 2;
    part0 = x - 1 - part1;
    input1 = make_shared<InputNode>(true, x);
    input2 = make_shared<InputNode>(false, y);
    // Prechecks
    // x0 is greater or equal than x1, so if x0y0 is mapped on A LUT then also x1y1 is mapped in a LUT
    if(Multiplier::isLUTMapped(part0 + 1, part0 + 1, multiplier) == true && this->LUT_solution == true)
    {
        // We want to return just a solution with just LUTs
        return MultiplicationTree();
    }
    // Checkin if x1 * y1 can be mapped in a LUT
    if(Multiplier::isLUTMapped(part1 + 1, part1 + 1, multiplier) == true)
    {
        multiplication_unit = make_shared<LUT>(part1 + 1, part1 + 1);
    }
    else
    {
        multiplication_unit = make_shared<Multiplier>(multiplier);
    }
    x1y1 = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
    // Operands of x1y1
    first_operand = Link(input1, part0, part1, false);
    second_operand = Link(input2, part0, part1, false);
    x1y1->insertOperandLast(first_operand);
    x1y1->insertOperandLast(second_operand);
    // Working on dxdy
    operation1 = make_shared<OperationNode>(make_shared<C2>());
    first_operand = Link(input1, 0, part0, false);
    operation1->insertOperandLast(first_operand);
    // Given that DX = x1 - x0 will not create overflow the length of the operation
    // will be the length of x0 (that is equal to x1 or equal to x1 + 1) + 1 for the sign
    dx = make_shared<OperationNode>(make_shared<Addition>());
    first_operand = Link(input1, part0, part1, false);
    second_operand = Link(operation1, 0, part0 + 1, true);
    dx->insertOperandLast(first_operand);
    dx->insertOperandLast(second_operand);
    first_operand = Link(input2, 0, part0, false);
    operation1 = make_shared<OperationNode>(make_shared<C2>());
    operation1->insertOperandLast(first_operand);
    first_operand = Link(input2, part0, part1, false);
    second_operand = Link(operation1, 0, part0 + 1, true);
    dy = make_shared<OperationNode>(make_shared<Addition>());
    dy->insertOperandLast(first_operand);
    dy->insertOperandLast(second_operand);
    // If x1y1 is mapped in a LUT, then maybe x0y0 can be mapped in a LUT too
    if(Multiplier::isLUTMapped(part0 + 1, part0 + 1, multiplier) == true)
    {
        this->LUT_solution = true;
        multiplication_unit = make_shared<LUT>(part0 + 1, part0 + 1);
    }
    else
    {
        multiplication_unit = make_shared<Multiplier>(multiplier);
    }
    x0y0 = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
    dxdy = make_shared<OperationNode>(make_shared<Multiplication>(multiplication_unit));
    // Operands of x0y0
    first_operand = Link(input1, 0, part0, false);
    second_operand = Link(input2, 0, part0, false);
    x0y0->insertOperandLast(first_operand);
    x0y0->insertOperandLast(second_operand);
    // Operands of dxdy
    first_operand = Link(dx);
    second_operand = Link(dy);
    dxdy->insertOperandLast(first_operand);
    dxdy->insertOperandLast(second_operand);
    // Computing x1y1 + x0y0 - dxdy remembering this operation as middle term
    operation1 = make_shared<OperationNode>(make_shared<Addition>());
    first_operand = Link(x1y1);
    second_operand = Link(x0y0);
    operation1->insertOperandLast(first_operand);
    operation1->insertOperandLast(second_operand);
    operation2 = make_shared<OperationNode>(make_shared<C2>());
    first_operand = Link(dxdy);
    operation2->insertOperandLast(first_operand);
    operation3 = make_shared<OperationNode>(make_shared<Addition>());
    first_operand = Link(operation1);
    second_operand = Link(operation2);
    operation3->insertOperandLast(first_operand);
    operation3->insertOperandLast(second_operand);
    // Operation3 contains middle term
    // x1y1 needs to be shifted
    operation1 = make_shared<OperationNode>(make_shared<Shift>(part0 * 2));
    first_operand = Link(x1y1);
    operation1->insertOperandLast(first_operand);
    // Middle term needs to be shifted
    operation2 = make_shared<OperationNode>(make_shared<Shift>(part0));
    first_operand = Link(operation3);
    operation2->insertOperandLast(first_operand);
    // x1y1 + x0y0
    operation3 = make_shared<OperationNode>(make_shared<Addition>());
    first_operand = Link(operation1);
    second_operand = Link(x0y0);
    operation3->insertOperandLast(first_operand);
    operation3->insertOperandLast(second_operand);
    // Adding signed operation
    if(this->sign_operations_included == true)
    {
        operation1 = make_shared<OperationNode>(make_shared<Addition>());
        first_operand = Link(operation3);
        second_operand = Link(Algorithm::addSignedOperation(x, y, input1, input2));
        operation1->insertOperandLast(first_operand);
        operation1->insertOperandLast(second_operand);
    }
    // Creating root
    root = make_shared<OperationNode>(make_shared<Addition>());
    if(this->sign_operations_included == true)
    {
        first_operand = Link(operation1);
    }
    else
    {
        first_operand = Link(operation3);
    }
    second_operand = Link(operation2);
    root->insertOperandLast(first_operand);
    root->insertOperandLast(second_operand);
    return MultiplicationTree(root, "Karatsuba-Ofman 2 way split (standard algorithm)", x, y);
}

vector<MultiplicationTree> KaratsubaOfman2::recursiveDisposition(int x, int y, Multiplier multiplier)
{
    vector<MultiplicationTree> multiplication_trees, returned_trees0, returned_trees1, returned_treesd, returned_trees;
    vector<shared_ptr<Algorithm>> algorithms;
    vector<Multiplier> multipliers;
    vector<OperationNode*> empty;
    int part0, part1, i, j, k;
    shared_ptr<InputNode> input1, input2;
    shared_ptr<OperationNode> x0y0, x1y1, dx, dy, dxdy, operation1, operation2, operation3, root;
    Link first_operand, second_operand, first_operand2, second_operand2;
    shared_ptr<MultiplicationUnit> multiplication_unit;
    MultiplicationTree tmp;

    // Preparing algorithms
    multipliers.push_back(multiplier);
    algorithms.push_back(make_shared<StandardTiling>(multipliers));
    algorithms.push_back(make_shared<ProposedTiling>(multipliers));
    algorithms.push_back(make_shared<KaratsubaOfman2>(multipliers));
    // Preparing lengths
    part1 = (x - 1) / 2;
    part0 = x - 1 - part1;
    for(i = 0; i < algorithms.size(); i++)
    {
        multiplication_trees = (algorithms[i])->dispositions(part0 + 1, part0 + 1);
        for(j = 0; j < multiplication_trees.size(); j++)
        {
            returned_treesd.push_back(multiplication_trees[j]);
        }
        (algorithms[i])->setSignOperationsIncluded(false);
        multiplication_trees = (algorithms[i])->dispositions(part0 + 1, part0 + 1);
        for(j = 0; j < multiplication_trees.size(); j++)
        {
            returned_trees0.push_back(multiplication_trees[j]);
        }
    }
    if(part1 == part0)
    {
        for(i = 0; i < returned_trees0.size(); i++)
        {
            returned_trees1.push_back(returned_trees0[i].copyTree());
        }
    }
    else
    {
        for(i = 0; i < algorithms.size(); i++)
        {
            multiplication_trees = (algorithms[i])->dispositions(part1 + 1, part1 + 1);
            for(j = 0; j < multiplication_trees.size(); j++)
            {
                returned_trees1.push_back(multiplication_trees[j]);
            }
        }
    }
    // returned trees 0 is used for the first quadrant
    // returned trees d is used for dxdy
    // returned trees 1 is used for the last quadrant
    for(i = 0; i < returned_trees0.size(); i++)
    {
        for(j = 0; j < returned_treesd.size(); j++)
        {
            for(k = 0; k < returned_trees1.size(); k++)
            {
                input1 = make_shared<InputNode>(true, x);
                input2 = make_shared<InputNode>(false, y);
                tmp = returned_trees0[i].copyTree();
                // Working on x0y0
                x0y0 = tmp.getRoot();
                x0y0->substituteLeaves(input1, input2);
                // Working on dxdy
                operation1 = make_shared<OperationNode>(make_shared<C2>());
                first_operand = Link(input1, 0, part0, false);
                operation1->insertOperandLast(first_operand);
                dx = make_shared<OperationNode>(make_shared<Addition>());
                first_operand = Link(input1, part0, part1, false);
                second_operand = Link(operation1, 0, part0 + 1, true);
                dx->insertOperandLast(first_operand);
                dx->insertOperandLast(second_operand);
                first_operand = Link(input2, 0, part0, false);
                operation1 = make_shared<OperationNode>(make_shared<C2>());
                operation1->insertOperandLast(first_operand);
                first_operand = Link(input2, part0, part1, false);
                second_operand = Link(operation1, 0, part0 + 1, true);
                dy = make_shared<OperationNode>(make_shared<Addition>());
                dy->insertOperandLast(first_operand);
                dy->insertOperandLast(second_operand);
                tmp = returned_treesd[j].copyTree();
                dxdy = tmp.getRoot();
                dxdy->substituteLeaves(dx, dy);
                // working in x1y1
                tmp = returned_trees1[k].copyTree();
                x1y1 = tmp.getRoot();
                x1y1->substituteLeaves(input1, input2);
                x1y1->shiftLinksOperands(part0, part0, empty);
                // Computing x1y1 + x0y0 - dxdy remembering this operation as middle term
                operation1 = make_shared<OperationNode>(make_shared<Addition>());
                first_operand = Link(x1y1);
                second_operand = Link(x0y0);
                operation1->insertOperandLast(first_operand);
                operation1->insertOperandLast(second_operand);
                operation2 = make_shared<OperationNode>(make_shared<C2>());
                first_operand = Link(dxdy);
                operation2->insertOperandLast(first_operand);
                operation3 = make_shared<OperationNode>(make_shared<Addition>());
                first_operand = Link(operation1);
                second_operand = Link(operation2);
                operation3->insertOperandLast(first_operand);
                operation3->insertOperandLast(second_operand);
                // Operation3 contains middle term
                // x1y1 needs to be shifted
                operation1 = make_shared<OperationNode>(make_shared<Shift>(part0 * 2));
                first_operand = Link(x1y1);
                operation1->insertOperandLast(first_operand);
                // Middle term needs to be shifted
                operation2 = make_shared<OperationNode>(make_shared<Shift>(part0));
                first_operand = Link(operation3);
                operation2->insertOperandLast(first_operand);
                // x1y1 + x0y0
                operation3 = make_shared<OperationNode>(make_shared<Addition>());
                first_operand = Link(operation1);
                second_operand = Link(x0y0);
                operation3->insertOperandLast(first_operand);
                operation3->insertOperandLast(second_operand);
                // Adding signed operation
                if(this->sign_operations_included == true)
                {
                    operation1 = make_shared<OperationNode>(make_shared<Addition>());
                    first_operand = Link(operation3);
                    second_operand = Link(Algorithm::addSignedOperation(x, y, input1, input2));
                    operation1->insertOperandLast(first_operand);
                    operation1->insertOperandLast(second_operand);
                }
                // Creating root
                root = make_shared<OperationNode>(make_shared<Addition>());
                if(this->sign_operations_included == true)
                {
                    first_operand = Link(operation1);
                }
                else
                {
                    first_operand = Link(operation3);
                }
                second_operand = Link(operation2);
                root->insertOperandLast(first_operand);
                root->insertOperandLast(second_operand);
                returned_trees.push_back(MultiplicationTree(root, "Karatsuba-Ofman 2 way split (recursive algorithm)", x, y));
            }
        }
    }
    return returned_trees;
}
