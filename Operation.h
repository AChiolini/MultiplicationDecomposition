#ifndef OPERATION_H
#define OPERATION_H

enum OperationType
{
    ADDITION = 0,
    SUBTRACTION,
    SUBMULTIPLICATION,
};

class Operation 
{        
    public:
        virtual OperationType type() = 0;
        virtual ~Operation() = default;
};

#endif
