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

int priority(std::string op) {
	if (op == "||" || op == "|")
        return 0;
    if (op == "&&" || op == "&")
        return 1;
    if (op == "=>")
        return 2;
    if (op == "xor")
        return 3;
    if (op == "<=>")
        return 4;
    if (op == "!")
        return 5;
    return -1;
}

std::string BDD::comp(std::string n1, std::string n2, std::string o) {
	bool b1 = n1 == "true";
	bool b2 = n2 == "true";
	std::string res;

    res = op(o, b2, b1) ? "true" : "false";

	return res;
}

bool BDD::compute() {
	std::stack<std::string> tmp;

	//Expression vide.
	if(m_rpn.empty()) return false;

	while(!m_rpn.empty()) {
		std::string c = m_rpn.front();
		m_rpn.pop();

		//Si c'est un opérateur de négation, on inverse le booléen de la pile.
		if(c == "!" && !tmp.empty()) {
			std::string t = tmp.top();
			t = t == "true" ? "false" : "true";
			tmp.pop();
			tmp.push(t);
		//Si c'est | ou &, on effectue le calcul et on ajoute le résultat sur
		//la pile.
		} else if(priority(c) >= 0) {
			std::string n1 = tmp.top();
			tmp.pop();
			std::string n2 = tmp.top();
			tmp.pop();
			tmp.push(comp(n1, n2, c));
		//Si c'est un booléen (1 ou 0) on l'ajoute sur la pile.
		} else {
			tmp.push(c);
		}
	}
    return tmp.top() == "true";
}

void BDD::toRPN(std::vector<std::string> tab){
	std::stack<std::string> tmp;

	//On vide la pile rpn.
	while(!m_rpn.empty()) {
		m_rpn.pop();
	}

	std::string c;

	//Dernier indice de parenthèse ouvrante pour retrouver l'indice d'un
	//enventuel mauvais parenthésage.
	int lastLParInd = 0;

	for(unsigned int i = 0; i < tab.size() ; i++) {
		c = tab[i];

		int po = priority(c);

		//On a un 1 ou 0.
		if(c == "true" || c == "false") {
			//On ajoute sur la pile.
			m_rpn.push(c);
			//On met sur la sortie un ! si nécessaire.
			int nbNotOp = 0;
			while(!tmp.empty() && tmp.top() == "!") {
				nbNotOp++;
				tmp.pop();
			}
			if(nbNotOp % 2 == 1) {
				m_rpn.push("!");
			}
		//On a un & ou un |.
		} else if(po >= 0) {
			if(!tmp.empty() && c != "!") {
				std::string op2 = tmp.top();
				int po2 = priority(op2);
				//On ajoute l'opérateur sur la sortie si sa priorité est
				//inférieure à celle du premier opérateur de la pile.
				if(po <= po2) {
					tmp.pop();
					m_rpn.push(op2);
				}
			}
			//On ajoute l'opérateur dans la pile.
			tmp.push(c);
		//On a une parenthèse gauche.
		} else if(c == "(") {
			lastLParInd = i;
			//On ajoute sur la pile.
			tmp.push(c);
			//On met sur la sortie un ! si nécessaire.
			int nbNotOp = 0;
			while(!tmp.empty() && tmp.top() == "!") {
				nbNotOp++;
				tmp.pop();
			}
			if(nbNotOp % 2 == 1) {
				m_rpn.push("!");
			}
		//On a une parenthèse droite.
		} else if(c == ")") {
			//On met sur la sortie tous ce qu'il t a avant la prochaine
			//parenthèse gauche.
			while(!tmp.empty() && tmp.top() != "(") {
				m_rpn.push(tmp.top());
				tmp.pop();
			}
            tmp.pop();
		}
	}

	//On ajoute sur la sortie le reste de la pile.
	while(!tmp.empty()) {
		m_rpn.push(tmp.top());
		tmp.pop();
	}
}

bool BDD::eval(std::vector<std::string> tab) {
	toRPN(tab);
	return compute();
}

Node* BDD::buildprime(std::vector<bool> vect, int i)
{
    if (i > vect.size())
    {
        std::vector<std::string> tab = parse(this->getExpression());
        std::vector<std::pair<int, std::string> > var;
        for (int c = 0; c < tab.size(); c++)
        {
            std::string t = tab[c];
            if (t != "&" && t != "&&" && t != "||" && t != "|" && t != "!" && t != "=>" && t != "<=>" && t != "xor" && t != "(" && t != ")")
            {
                std::string tmp = t.substr(0,1);
                if (tmp == "!")
                {
                    std::string tempo = t.substr(1,1);
                    if (tempo != "(")
                    {
                        std::string temp = t.substr(1,t.size()-1);
                        tab[c] = temp;
                        std::vector<std::string>::iterator it;
                        it = tab.begin();
                        tab.insert(it+c, "!");
                        var.push_back(std::make_pair(c+1, temp));
                    }
                    else
                    {
                        std::string temp = t.substr(2,t.size()-2);
                        tab[c] = temp;
                        std::vector<std::string>::iterator it;
                        it = tab.begin();
                        tab.insert(it+c, "!");
                        it = tab.begin();
                        tab.insert(it+c+1, "(");
                        var.push_back(std::make_pair(c+2, temp));
                    }
                }
                else if (tmp == "(")
                {
                    std::string tempo = t.substr(1,1);
                    if (tempo != "!")
                    {
                        std::string temp = t.substr(1,t.size()-1);
                        tab[c] = temp;
                        std::vector<std::string>::iterator it;
                        it = tab.begin();
                        tab.insert(it+c, "(");
                        var.push_back(std::make_pair(c+1, temp));
                    }
                    else
                    {
                        std::string temp = t.substr(2,t.size()-2);
                        tab[c] = temp;
                        std::vector<std::string>::iterator it;
                        it = tab.begin();
                        tab.insert(it+c, "(");
                        it = tab.begin();
                        tab.insert(it+c+1, "!");
                        var.push_back(std::make_pair(c+2, temp));
                    }
                }
                else
                {
                    std::string tempo = t.substr(t.size()-1,1);
                    if (tempo == ")")
                    {
                        std::string temp = t.substr(0,t.size()-1);
                        tab[c] = temp;
                        std::vector<std::string>::iterator it;
                        it = tab.begin();
                        tab.insert(it+c+1, ")");
                        var.push_back(std::make_pair(c, temp));
                    }
                    else
                        var.push_back(std::make_pair(c, t));
                }
            }
        }
        std::vector<std::pair<std::string, int> > varfinal;
        int number =0;
        for (int count =0; count < var.size(); count++)
        {
            std::pair<bool,int> pair = find(varfinal, var[count].second);
            if (pair.first==false)
            {
                varfinal.push_back(std::make_pair(var[count].second, number));
                number++;
            }
            else
            {
                varfinal.push_back(std::make_pair(var[count].second, pair.second));
            }
        }
        if (vect.size() != number)
            throw number;
        for (int c=0; c < var.size(); c++)
        {
            std::pair<int, std::string> pair1 = var[c];
            std::pair<std::string, int> pair2 = varfinal[c];
            bool tmp = vect[pair2.second];
            if (tmp)
                tab[pair1.first] = "true";
            else
                tab[pair1.first] = "false";
        }
        for (int c = 0; c < tab.size(); c++)
        {
            std::cout << tab[c] << " ";
        }
        bool res = eval(tab);
        std::cout << "; valeur finale :";
        if (res==false)
        {
            std::cout << "false" << std::endl;
            return this->nodeFalse;
        }
        else
        {
            std::cout << "true" << std::endl;
            return this->nodeTrue;
        }
        //std::cout << var.size() << ";" << op.size() << ";" << res << std::endl;
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
    if (o == "&" || o == "&&")
    {
        return (b1 && b2);
    }
    if (o == "|" || o == "||")
    {
        return (b1 || b2);
    }
    if (o == "=>")
    {
        return (!b1 || b2);
    }
    if (o == "xor")
    {
        return ((b1 && !b2) || (!b1 && b2));
    }
    if (o == "<=>")
    {
        return ((!b1 || b2) && (b1 || !b2));
    }
    else
    {
        return (b1 || b2);
    }
}

int puissance(int a, int b)
{
    int res = 1;
    for (int i=1; i <= b; i++)
    {
        res = res * a;
    }
    return res;
}

int BDD::count(Node* node)
{
    int res = 0;
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
        res = puissance(2,(node->getLhs()->getIndice() - node->getIndice() - 1))*count(node->getLhs()) +
            puissance(2,(node->getRhs()->getIndice() - node->getIndice() - 1))*count(node->getRhs());
    }
    return res;
}

int BDD::satcount(Node* node)
{
    return (puissance(2,(node->getIndice() - 1))*count(node));
}
