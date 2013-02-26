#ifndef BDD_H
#define BDD_H

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <iterator>
#include <utility>
#include <string>
#include <stack>
#include <queue>
#include<stdio.h>
#include<stdlib.h>
#include <algorithm>
#include "Node.h"

class BDD
{
    public:
        BDD();
        virtual ~BDD();
        int getNbVar();
        std::string getExpression();
        std::vector<bool> getVector();
        std::vector<std::string> getVectVar();
        std::map<std::pair<int,std::pair<Node*,Node*> >,Node*> getVectNode();
        std::vector<Node*> getVectorNode();
        void setNbVar(int nbvar);
        void setExpression(std::string expr);
        Node* build();
        Node* buildprime(std::vector<bool> vect, int i);
        Node* MK(int i, Node* l, Node* r);
        Node* APP(std::string op, Node* u1, Node* u2, std::map<std::pair<Node*, Node*>,Node*> map);
        Node* APPLY(std::string op, BDD u1, BDD u2);
        bool op(std::string o, bool b1, bool b2);
        int satcount();
        int count(Node* node);
        void toRPN(std::vector<std::string> tab);
        bool compute();
        std::string comp(std::string n1, std::string n2, std::string op);
        bool eval(std::vector<std::string> tab);
        std::string anysataux(Node* node);
        std::string anysat();
        Node* getTopNode();
        void setTopNode(Node* node);
        std::string drawbis(Node* node);
        std::string draw();
        Node* restr(int indVar, bool val);
        Node* res(Node* node, int indVar, bool val);
    protected:
    private:
        int nbVar;
        std::string expression;
        std::vector<bool> vect;
        std::vector<std::string> vectVar;
        std::vector<Node*> vectorNode;
        std::map<std::pair<int,std::pair<Node*,Node*> >,Node*> vectNode;
        Node* nodeFalse;
        Node* nodeTrue;
        std::queue<std::string> m_rpn;
        Node* topNode;
};

#endif // BDD_H
