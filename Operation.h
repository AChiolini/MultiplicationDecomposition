#ifndef OPERATION_H
#define OPERATION_H

class Operation 
{        
    public:
        virtual int OperationID() = 0;
        virtual ~Operation() = default;
};

#endif
