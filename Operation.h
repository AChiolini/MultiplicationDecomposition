#ifndef OPERATION_H
#define OPERATION_H

enum OperationType
{
    ADDITION = 1,
    SUBTRACTION,
    SUBMULTIPLICATION,
    SHIFT
};

class Operation 
{        
    public:
        virtual OperationType getOperationType() = 0;
        virtual ~Operation() = default;
};

#endif
