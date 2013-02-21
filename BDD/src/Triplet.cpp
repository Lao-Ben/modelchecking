#include "../include/Triplet.h"

Triplet::Triplet()
{
    //ctor
}

Triplet::Triplet(int i, Node* l, Node* r)
{
    this->ind = i;
    this->lhs = l;
    this->rhs = r;
}

Triplet::~Triplet()
{
    //dtor
}
