#ifndef BDD_H
#define BDD_H

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <iterator>
#include <utility>
#include <string>
#include <algorithm>
#include "Node.h"
#include "Triplet.h"

class BDD
{
    public:
        BDD();
        virtual ~BDD();
        int getNbVar();
        std::string getExpression();
        std::vector<bool> getVector();
        std::map<std::pair<int,std::pair<Node*,Node*> >,Node*> getVectNode();
        std::vector<Node*> getVectorNode();
        void setNbVar(int nbvar);
        void setExpression(std::string expr);
        Node* build();
        Node* buildprime(std::vector<bool> vect, int i);
        Node* MK(int i, Node* l, Node* r);
        Node* APP(std::string op, Node* u1, Node* u2, std::map<std::pair<Node*, Node*>,Node*> map);
        Node* APPLY(std::string op, Node* u1, Node* u2);
        bool op(std::string o, bool b1, bool b2);
        int satcount(Node* node);
        int count(Node* node);
    protected:
    private:
        int nbVar;
        std::string expression;
        std::vector<bool> vect;
        std::vector<Node*> vectorNode;
        std::map<std::pair<int,std::pair<Node*,Node*> >,Node*> vectNode;
        Node* nodeFalse;
        Node* nodeTrue;
};

#endif // BDD_H