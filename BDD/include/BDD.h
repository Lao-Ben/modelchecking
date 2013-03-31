#ifndef BDD_H
#define BDD_H

#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iterator>
#include <utility>
#include <string>
#include <stack>
#include <queue>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <ostream>
#include "Node.h"

class BDD
{
    public:
        BDD();
        BDD(int nbVar, std::vector<std::string> vectVar, std::vector<Node*> vectorNode, std::unordered_map<std::string,Node*> vectNode, Node* nodeFalse, Node* nodeTrue, std::unordered_map<std::string, int> varorder, std::unordered_map<int, std::string> ordervar, int maxindice, std::unordered_map<std::string,Node*> opmap);
        virtual ~BDD();
        int getNbVar();
        std::string getExpression();
        std::vector<bool> getVector();
        std::vector<std::string> getVectVar();
        std::unordered_map<std::string,Node*> getVectNode();
        std::vector<Node*> getVectorNode();
        void setVectVar(std::vector<std::string> v);
        void setVectNode(std::unordered_map<std::string,Node*> v);
        void setVectorNode(std::vector<Node*> v);
        void setNbVar(int nbvar);
        void setExpression(std::string expr);
        Node* build();
        Node* build(bool print);
        Node* buildprime(std::vector<bool> vect, int i, bool print, std::vector<std::string> tab, std::vector<std::pair<int, std::string> > var, std::vector<int> tabtemp);
        Node* MK(int i, Node* l, Node* r);
        Node* APP(std::string op, Node* u1, Node* u2);
        Node* APPLY(std::string op, BDD u1, BDD u2);
        bool op(std::string o, bool b1, bool b2);
        int satcount();
        int count(Node* node);
        void toRPN(std::vector<std::string> tab);
        bool compute();
        std::string comp(std::string n1, std::string n2, std::string op);
        bool eval(std::vector<std::string> tab);
        std::string anysat();
        Node* getTopNode();
        void setTopNode(Node* node);
        std::string draw();
        Node* restr(int indVar, bool val);
        Node* res(Node* node, int indVar, bool val);
        void allsat();
        void testeval(std::string e, bool val);
        void printGraph();
        BDD* andfonc (BDD* bdd1, std::string s);
        BDD* andfonc (BDD* bdd1, BDD* bdd2);
        BDD* orfonc (BDD* bdd1, std::string s);
        BDD* orfonc (BDD* bdd1, BDD* bdd2);
        int getMaxIndice();
        void setMaxIndice(int m);
        Node* getNodeFalse();
        Node* getNodeTrue();
        std::unordered_map<std::string, int> getVarorder();
        std::unordered_map<int, std::string> getOrdervar();
        void setVarorder(std::unordered_map<std::string, int> v);
        void setOrdervar(std::unordered_map<int, std::string> o);
        BDD* transferinfo(BDD* bdd1, BDD* bdd2);
        std::unordered_map<std::string,Node*> getOpmap();
        void setOpmap(std::unordered_map<std::string,Node*> v);
        void toDot (const std::string& filename);
        void toDot (std::ostream& out, Node* node);
    protected:
    private:
        Node* APP2(std::string op, Node* u1, Node* u2);
        std::string anysataux(Node* node);
        std::string drawbis(Node* node);
        std::string op2(std::string o, std::string b1, std::string b2);
        void compute2();
        std::string comp2(std::string n1, std::string n2, std::string op);
        void toRPN2(std::vector<std::string> tab);
        void parray(std::vector<int> A, int level);
        void allsat_rec(Node* node, std::vector<int> A, int level);
        std::string getInfoNode(int indice);
        void printGraphbis(Node* node, int nbesp);
        void bddReduction();
        void  _toDot (std::ostream& out, Node* node);
        int nbVar;
        std::string expression;
        std::vector<bool> vect;
        std::vector<std::string> vectVar;
        std::vector<Node*> vectorNode;
        std::unordered_map<std::string,Node*> vectNode;
        std::queue<std::string> m_rpn;
        Node* topNode;
        Node* nodeFalse;
        Node* nodeTrue;
        std::unordered_map<std::string, int> varorder;
        std::unordered_map<int, std::string> ordervar;
        int maxindice;
        std::unordered_map<std::string,Node*> opmap;
};

#endif // BDD_H
