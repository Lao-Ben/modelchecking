#include "../include/BDD.h"
#include <stdlib.h>
#include <math.h>

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
    this->vectVar = std::vector<std::string>(nbVar);
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
    return build(false);
}

Node* BDD::build(bool print)
{
    try {
        Node* n = this->buildprime(this->vect, 1, print);
        this->setTopNode(n);
        return n;
    } catch (int code) {
        std::cerr << "Exception : Not enough variable. Give " << this->nbVar << " but need " << code << std::endl;
        return NULL;
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
	if (op == "=>")
    return 0;
  if (op == "<=>")
    return 1;
  if (op == "xor")
    return 2;
  if (op == "||" || op == "|")
    return 3;
  if (op == "&&" || op == "&")
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

Node* BDD::buildprime(std::vector<bool> vect, int i, bool print)
{
    if (i > vect.size())
    {
        std::vector<std::string> tab = parse(this->getExpression());
        std::vector<std::pair<int, std::string> > var;
        for (int c = 0; c < tab.size(); c++)
        {
            std::string t = tab[c];
            if (t != "&" && t != "&&" && t != "||" && t != "|" && t != "!" && t != "=>" && t != "<=>" && t != "xor" && t != "(" && t != ")" && t!="true" && t!="false")
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
            this->vectVar[pair2.second] = pair2.first;
            if (tmp)
                tab[pair1.first] = "true";
            else
                tab[pair1.first] = "false";
        }
        if (print)
            for (int c = 0; c < tab.size(); c++)
            {
                std::cout << tab[c] << " ";
            }
        bool res = eval(tab);
        if (print)
            std::cout << "; valeur finale :";
        if (res==false)
        {
            if (print)
                std::cout << "false" << std::endl;
            return this->nodeFalse;
        }
        else
        {
            if (print)
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
        Node* v0 = buildprime(vect0,i+1, print);
        Node* v1 = buildprime(vect1,i+1, print);
        return this->MK(i, v0, v1);
    }
}

Node* BDD::restr(int indVar, bool val)
{
    return (res(this->getTopNode(), indVar, val));
}

Node* BDD::res(Node* node, int indVar, bool val)
{
    if (node->getIndice() > indVar)
    {
        return node;
    }
    else if (node->getIndice() < indVar)
    {
        return MK(node->getIndice(), res(node->getLhs(), indVar, val), res(node->getRhs(), indVar, val));
    }
    else
    {
        if (val == false)
        {
            return res(node->getRhs(), indVar, val);
        }
        else
        {
            return res(node->getLhs(), indVar, val);
        }
    }
}

void BDD::parray(std::vector<int> A, int level) {
    std::vector<std::vector<std::string> > tab = std::vector<std::vector<std::string> >(1);
    for (int i = 1; i < level; i++)
    {
        std::string s = "[" + this->getVectVar()[i-1] + ":";
        if (A[i] < 0)
        {
            int nb = tab.size();
            for (int j = 0; j < nb; j++)
                tab.push_back(tab[j]);
            for (int j = 0; j < tab.size(); j++)
            {
                if (j % 2 == 0)
                    tab[j].push_back(s+"true");
                else
                    tab[j].push_back(s+"false");
            }
        }
        else
        {
            if (A[i] == 0)
            {
                for (int j = 0; j < tab.size(); j++)
                {
                    tab[j].push_back(s+"false");
                }
            }
            else
            {
                for (int j = 0; j < tab.size(); j++)
                {
                    tab[j].push_back(s+"true");
                }
            }
        }
    }
    for (int i = 0; i < tab.size(); i++)
    {
        for (int j=0; j < tab[i].size(); j++)
        {
            if (j != 0)
                std::cout << ",";
            std::cout << tab[i][j];
        }
        for (int j = 1; j < level; j++)
            std::cout << "]";
        std::cout << "=true" << std::endl;
    }
}

void BDD::allsat_rec(Node* node, std::vector<int> A, int level)
{
  int v = node->getIndice();
  while (level < v) {
    A[level] = -1;		/* mark redundant tests as -1 */
    level++;
  }

  if (node->isLeaf() && node->getValue()) {
    parray(A, level);
    return;
  }
  if (!(node->getRhs()->isLeaf() && (node->getRhs()->getValue() == false))) {
    A[v] = 0;
    allsat_rec(node->getRhs(), A, v+1);
  }
  if (!(node->getLhs()->isLeaf() && (node->getLhs()->getValue() == false))) {
    A[v] = 1;
    allsat_rec(node->getLhs(), A, v+1);
  }
  return;
}

void BDD::allsat()
{
    Node* node = this->getTopNode();
    if (node->isLeaf() && (node->getValue() == false)) {
        printf("no solutions");
    } else {
        std::vector<int> A = std::vector<int>(this->nbVar+1);
        allsat_rec(node, A, 1);
    }
}

std::string BDD::anysat()
{
    return this->anysataux(this->getTopNode());
}

std::string BDD::anysataux(Node* node)
{
    std::string s = "";
    if (node->isLeaf())
    {
        if (node->getValue() == false)
        {
            return "error";
        }
        else
        {
            return "[]";
        }
    }
    else
    {
        if (node->getRhs()->isLeaf() == true && node->getRhs()->getValue() == false)
        {
            std::string str = anysataux(node->getLhs());
            if (str != "error")
            {
                s = "["+ this->getVectVar()[node->getIndice()-1] +":true;"+str+"]";
                return (s);
            }
            else
            {
                s = "["+ this->getVectVar()[node->getIndice()-1] +":false;"+anysataux(node->getRhs())+"]";
                return (s);
            }
        }
        else
        {
            std::string str = anysataux(node->getRhs());
            if (str != "error")
            {
                s = "["+ this->getVectVar()[node->getIndice()-1] +":false;"+str+"]";
                return (s);
            }
            else
            {
                s = "["+ this->getVectVar()[node->getIndice()-1] +":true;"+anysataux(node->getLhs())+"]";
                return (s);
            }
        }
        return "";
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
        Node* node;
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
            node = this->MK(u2->getIndice(), this->APP(op,u1, u2->getLhs(), map), this->APP(op,u1, u2->getRhs(), map));
        }
        map.insert(std::make_pair(std::make_pair(u1,u2), node));
        return node;
    }
}

void setIndLeaf(Node* node, int val)
{
    if (node != NULL)
    {
        if (node->isLeaf())
            node->setIndice(val);
        else
        {
            setIndLeaf(node->getLhs(), val);
            setIndLeaf(node->getRhs(), val);
        }
    }
}

Node* BDD::APPLY(std::string op, BDD bdd1, BDD bdd2)
{
    Node* u1 = bdd1.getTopNode();
    Node* u2 = bdd2.getTopNode();
    std::cout << "(" << bdd1.getExpression() << ") " << op << " (" << bdd2.getExpression() << ")" << std::endl;
    this->expression = "( " + bdd1.getExpression() + " ) " + op + " ( " + bdd2.getExpression() + " )";
    std::map<std::pair<Node*, Node*>,Node*> map;
    int size1 = bdd1.getVector().size();
    int size2 = bdd2.getVector().size();
    if (size1 < size2)
    {
        this->vect = bdd2.getVector();
        this->vectVar = bdd2.getVectVar();
    }
    else
    {
        this->vect = bdd1.getVector();
        this->vectVar = bdd1.getVectVar();
    }
    this->nbVar = this->vect.size();
    this->nodeFalse->setIndice(this->vect.size()+1);
    this->nodeTrue->setIndice(this->vect.size()+1);
    setIndLeaf(u1, this->vect.size()+1);
    setIndLeaf(u2, this->vect.size()+1);
    Node* node = this->APP(op, u1, u2, map);
    setIndLeaf(u1, size1+1);
    setIndLeaf(u2, size2+1);
    this->setTopNode(node);
    return node;
}

std::vector<std::string> BDD::getVectVar()
{
    return this->vectVar;
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
        res = pow(2,(node->getLhs()->getIndice() - node->getIndice() - 1))*count(node->getLhs()) +
            pow(2,(node->getRhs()->getIndice() - node->getIndice() - 1))*count(node->getRhs());
    }
    return res;
}

int BDD::satcount()
{
    Node* node = this->getTopNode();
    return (pow(2,(node->getIndice() - 1))*count(node));
}

Node* BDD::getTopNode()
{
    return this->topNode;
}
void BDD::setTopNode(Node* node)
{
    this->topNode = node;
}

std::string BDD::draw()
{
    return this->drawbis(this->getTopNode());
}

std::string BDD::drawbis(Node* node)
{
    if (node == NULL)
        return "NULL";
    else if (node->isLeaf())
    {
        if (node->getValue() == true)
            return "true";
        else
            return "false";
    }
    else
    {
        std::string s = this->vectVar[node->getIndice()-1];
        return (s + "(" + drawbis(node->getLhs())+";"+drawbis(node->getRhs())+")");
    }
}
