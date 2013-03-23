#include "../include/Node.h"
#include <stdlib.h>

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 Node::~Node()
{

}

Node::Node(int i, Node* l, Node* r)
{
    this->indice = i;
    this->lhs = l;
    this->rhs = r;
    this->value = -1;
    this->leaf = false;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Node::setRhs(Node* r)
{
    this->rhs = r;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Node::setLhs(Node* l)
{
    this->lhs = l;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Node* Node::getRhs()
{
    return this->rhs;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
Node* Node::getLhs()
{
    return this->lhs;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 Node::Node()
{
    this->lhs = NULL;
    this->rhs = NULL;
    this->indice = 0;
    this->value = -1;
    this->leaf = false;
}

void Node::setValue(bool val)
{
    this->value = val;
}

bool Node::getValue()
{
    return this->value;
}

bool Node::isLeaf()
{
    return this->leaf;
}

void Node::setLeaf(bool l)
{
    this->leaf = l;
}

void Node::setIndice(int i)
{
    this->indice = i;
}

int Node::getIndice()
{
    return this->indice;
}
