#ifndef TRIPLET_H
#define TRIPLET_H

#include "Node.h"

class Triplet
{
    public:
        Triplet();
        Triplet(int i, Node* l, Node* r);
        virtual ~Triplet();
        int ind;
        Node* lhs;
        Node* rhs;
    protected:
    private:
};

#endif // TRIPLET_H
