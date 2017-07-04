#ifndef OPERATION_H
#define OPERATION_H

class Operation 
{        
    public:
        virtual int OperationID() {return -1;};
        virtual ~Operation() = default;
};

#endif