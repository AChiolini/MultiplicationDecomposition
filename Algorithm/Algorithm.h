#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "../MultiplicationTree/MultiplicationTree.h"
#include "../ArithmeticUnit/MultiplicationUnit/Multiplier/Multiplier.h"
#include "../Node/InputNode.h"
#include "../Operation/Addition.h"
#include "../Operation/And.h"
#include "../Operation/C2.h"
#include "../Operation/Fanout.h"
#include "../Operation/Shift.h"

class Algorithm
{
    public:
        virtual vector <MultiplicationTree> dispositions (int, int) = 0;
        virtual ~Algorithm () = default;

        static shared_ptr<OperationNode> addSignedOperation(int x, int y, shared_ptr<InputNode> input1, shared_ptr<InputNode> input2)
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
            return operation2;
        }
};

#endif
