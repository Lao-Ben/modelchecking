#include "../include/BDD.h"
#include <stdlib.h>

BDD::BDD()
{
    //ctor
    Node* node1 = new Node();
    node1->setValue(false);
    node1->setLhs(NULL);
    node1->setRhs(NULL);
    node1->setLeaf(true);
    Node* node2 = new Node();
    node2->setValue(true);
    node2->setLhs(NULL);
    node2->setRhs(NULL);
    node2->setLeaf(true);
    this->nodeFalse = node1;
    this->nodeTrue = node2;
    this->setNbVar(0);
}

BDD::~BDD()
{
    //dtor
}
void BDD::setExpression(std::string expr)
{
    this->expression = expr;
}

void BDD::setNbVar(int nbvar)
{
    this->nbVar = nbvar;
    this->vect = std::vector<bool>(nbvar);
    this->nodeFalse->setIndice(nbvar+1);
    this->nodeTrue->setIndice(nbvar+1);
}

std::string BDD::getExpression()
{
    return this->expression;
}

int BDD::getNbVar()
{
    return this->nbVar;
}

std::vector<bool> BDD::getVector()
{
    return this->vect;
}

std::map<std::pair<int,std::pair<Node*,Node*> >,Node*> BDD::getVectNode()
{
    return this->vectNode;
}

std::vector<Node*> BDD::getVectorNode()
{
    return this->vectorNode;
}

Node* BDD::build()
{
    try {
        return this->buildprime(this->vect, 1);
    } catch (int code) {
        std::cerr << "Exception : Not enough variable. Give " << this->nbVar << " but need " << code << std::endl;
    }
}

std::vector<std::string> parse(std::string l)
{
    std::stringstream ss(l);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    return vstrings;
}

std::pair<bool,int> find(std::vector<std::pair<std::string, int> > vect, std::string s)
{
    int count = 0;
    for (count = 0; count < vect.size();count++)
    {
        if (vect[count].first == s)
            return std::make_pair(true,vect[count].second);
    }
    return std::make_pair(false,-1);
}

Node* BDD::buildprime(std::vector<bool> vect, int i)
{
    if (i > vect.size())
    {
        std::vector<std::string> tab = parse(this->getExpression());
        std::vector<std::string> var;
        std::vector<std::string> op;
        int count = 0;
        for (count = 0; count < (tab.size()/2 + 1); count++)
        {
            var.push_back(tab[2*count]);
            if (2*count +1 < (tab.size()))
                op.push_back(tab[2*count+1]);
        }
        std::vector<std::pair<std::string, int> > varfinal;
        int number =0;
        for (count =0; count < var.size(); count++)
        {
            std::pair<bool,int> pair = find(varfinal, var[count]);
            if (pair.first==false)
            {
                varfinal.push_back(std::make_pair(var[count], number));
                number++;
            }
            else
            {
                varfinal.push_back(std::make_pair(var[count], pair.second));
            }
        }
        if (vect.size() != number)
            throw number;
        bool res = vect[varfinal[0].second];
        std::cout << varfinal.size() << ";" << op.size() << "; nbVar:" << number << "; valeur:" << varfinal[0].first << ":" << res << ";";
        for (count=0; count < op.size(); count++)
        {
            bool temp = vect[varfinal[count+1].second];
            std::cout << varfinal[count+1].first << ":" << temp << ";";
            if (op[count]=="&")
            {
                res = res && temp;
            }
            else
            {
                res = res || temp;
            }
        }
        std::cout << "valeur final : " << res << std::endl;
        if (res==false)
        {
            return this->nodeFalse;
        }
        else
        {
            return this->nodeTrue;
        }
        std::cout << var.size() << ";" << op.size() << ";" << res << std::endl;
    }
    else
    {
        std::vector<bool> vect0 = vect;
        vect0[i-1] = true;
        std::vector<bool> vect1 = vect;
        vect1[i-1] = false;
        Node* v0 = buildprime(vect0,i+1);
        Node* v1 = buildprime(vect1,i+1);
        return this->MK(i, v0, v1);
    }
}

Node* BDD::MK(int i, Node* l, Node* r)
{
    if (l == r)
        return l;
    else if (this->vectNode.count(std::make_pair(i, std::make_pair(l,r)))==1)
        return this->vectNode.at(std::make_pair(i, std::make_pair(l,r)));
    else
    {
        Node* node = new Node(i,l,r);
        this->vectorNode.push_back(node);
        this->vectNode.insert(std::make_pair(std::make_pair(i, std::make_pair(l,r)), node));
        return node;
    }
}

Node* BDD::APP(std::string op, Node* u1, Node* u2, std::map<std::pair<Node*, Node*>,Node*> map)
{
    if (map.count(std::make_pair(u1,u2))==1)
    {
        return map.at(std::make_pair(u1,u2));
    }
    else
    {
        Node* node = new Node();
        if (u1->isLeaf() && u2->isLeaf())
        {
            if (this->op(op,u1->getValue(),u2->getValue()) == true)
            {
                node = this->nodeTrue;
            }
            else
            {
                node = this->nodeFalse;
            }
        }
        else if (u1->getIndice() == u2->getIndice())
        {
            node = this->MK(u1->getIndice(), this->APP(op,u1->getLhs(), u2->getLhs(), map), this->APP(op,u1->getRhs(), u2->getRhs(), map));
        }
        else if (u1->getIndice() < u2->getIndice())
        {
            node = this->MK(u1->getIndice(), this->APP(op,u1->getLhs(), u2, map), this->APP(op,u1->getRhs(), u2, map));
        }
        else
        {
            node = this->MK(u1->getIndice(), this->APP(op,u1, u2->getLhs(), map), this->APP(op,u1, u2->getRhs(), map));
        }
        map.insert(std::make_pair(std::make_pair(u1,u2), node));
        return node;
    }
}

Node* BDD::APPLY(std::string op, Node* u1, Node* u2)
{
    std::map<std::pair<Node*, Node*>,Node*> map;
    return this->APP(op, u1, u2, map);
}

bool BDD::op(std::string o, bool b1, bool b2)
{
    if (o == "&")
    {
        return (b1 && b2);
    }
    if (o == "|")
    {
        return (b1 || b2);
    }
    else
    {
        return (b1 || b2);
    }
}

int BDD::count(Node* node)
{
    int res = 0;
    int n = node->getIndice();
    if (node->isLeaf())
    {
        if (node->getValue()==true)
        {
            res = 1;
        }
        else
        {
            res = 0;
        }
    }
    else
    {
        int rhs = node->getRhs()->getIndice();
        int lhs = node->getLhs()->getIndice();
        res = 2^(node->getLhs()->getIndice() - node->getIndice() - 1)*count(node->getLhs()) +
            2^(node->getRhs()->getIndice() - node->getIndice() - 1)*count(node->getRhs());
    }
    return res;
}

int BDD::satcount(Node* node)
{
    return (2^(node->getIndice() - 1)*count(node));
}
