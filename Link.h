#ifndef LINK_H
#define LINK_H

#include <memory>

/* This class is used to specify how many bits an operation should retrieve
 * from a node, in order to perform correctly the entire multiplication.
 */

class Link
{
    private:
        shared_ptr<Node> node;
        int start;
        int length;
        bool sign_included;

    public:
        Link();
        Link(shared_ptr<Node>);
        Link(shared_ptr<Node>, int, int);
        Link(shared_ptr<Node>, int, int, bool);
        shared_ptr<Node> getNode();
        int getStart();
        int getLength();
        bool isSignIncluded();
        void setNode(shared_ptr<Node>);
        void setStart(int);
        void setLength(int);
        void setSignIncluded(bool);
        virtual ~Link() = default;
};

#endif
