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
    this->maxindice = 1;
    this->expression = "";
    this->topNode = NULL;
}

BDD::BDD(BDD& instance)
{
    this->nbVar = instance.getNbVar();
    this->expression = instance.getExpression();
    this->vect = instance.getVector();
    this->vectorNode = instance.getVectorNode();
    this->vectNode = instance.getVectNode();
    this->topNode = instance.getTopNode();
    this->nodeFalse = instance.getNodeFalse();
    this->nodeTrue = instance.getNodeTrue();
    this->varorder = instance.getVarorder();
    this->ordervar = instance.getOrdervar();
    this->maxindice = instance.getMaxIndice();
    this->opmap = instance.getOpmap();
}

BDD::BDD(int nbVarnew, std::vector<Node*> vectorNodenew, std::unordered_map<std::string,Node*> vectNodenew, Node* nodeFalsenew, Node* nodeTruenew, std::unordered_map<std::string, int> varordernew, std::unordered_map<int, std::string> ordervarnew, int maxindicenew, std::unordered_map<std::string,Node*> opmapnew)
{
    this->nbVar = nbVarnew;
    this->vectorNode = vectorNodenew;
    this->vectNode = vectNodenew;
    this->nodeFalse = nodeFalsenew;
    this->nodeTrue = nodeTruenew;
    this->varorder = varordernew;
    this->ordervar = ordervarnew;
    this->maxindice = maxindicenew;
    this->vect = std::vector<bool>(nbVarnew);
    this->opmap = opmapnew;
    this->expression = "";
    this->topNode = NULL;
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

std::unordered_map<std::string,Node*> BDD::getVectNode()
{
    return this->vectNode;
}

std::vector<Node*> BDD::getVectorNode()
{
    return this->vectorNode;
}

std::vector<std::string> BDD::parse(std::string l)
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
		else
		{
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

Node* BDD::build()
{
    return build(false);
}

Node* BDD::build(bool print)
{
    try {
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
                        c = c + 1;
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
                        c = c + 2;
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
                        c = c + 1;
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
                        c = c + 2;
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
        int number = this->maxindice;
        for (int count =0; count < var.size(); count++)
        {
            if (varorder.count(var[count].second) != 1)
            {
                varorder.insert(std::make_pair(var[count].second, number));
                ordervar.insert(std::make_pair(number, var[count].second));
                number++;
            }
        }
        if (vect.size() < (number-1))
            throw (number-1);
        this->maxindice = number;
        this->vect = std::vector<bool>(number-1);
        this->nodeFalse->setIndice(number);
        this->nodeTrue->setIndice(number);
        std::vector<int> tabtemp;
        for (int i=0; i < var.size(); i++)
        {
            std::pair<int, std::string> pair1 = var[i];
            int truepos = varorder.at(pair1.second);
            if (std::find(tabtemp.begin(), tabtemp.end(), truepos) == tabtemp.end())
                tabtemp.push_back(truepos);
        }
        std::sort (tabtemp.begin(), tabtemp.end());
        Node* n = this->buildprime(this->vect, 1, print, tab, var, tabtemp);
        this->setTopNode(n);
        return n;
    } catch (int code) {
        std::cerr << "Exception : Not enough variable. Give " << this->nbVar << " but need " << code << std::endl;
        return NULL;
    }
}

Node* BDD::buildprime(std::vector<bool> vect, int i, bool print, std::vector<std::string> tab, std::vector<std::pair<int, std::string> > var, std::vector<int> tabtemp)
{
    if (i > tabtemp.size())
    {
        for (int c=0; c < var.size(); c++)
        {
            std::pair<int, std::string> pair1 = var[c];
            int index = varorder.at(pair1.second)-1;
            bool tmp = vect[index];
            if (tmp)
                tab[pair1.first] = "true";
            else
                tab[pair1.first] = "false";
            //std::cout << tab[pair1.first] << "(" << pair1.second << ")";
        }
        //std::cout << std::endl;
        if (print)
            for (int c = 0; c < tab.size(); c++)
            {
                if (tab[c] == "&" || tab[c] == "&&" || tab[c] == "||" || tab[c] == "|" || tab[c] == "=>" || tab[c] == "<=>" || tab[c] == "xor")
                {
                    std::cout << " " << tab[c] << "(" << c << ")"<< " ";
                }
                else
                {
                    std::cout << tab[c] << "(" << c << ")";
                }
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
        vect0[tabtemp[i-1]-1] = true;
        std::vector<bool> vect1 = vect;
        vect1[tabtemp[i-1]-1] = false;
        Node* v0 = buildprime(vect0,i+1, print, tab, var, tabtemp);
        Node* v1 = buildprime(vect1,i+1, print, tab, var, tabtemp);

        Node* res = this->MK(tabtemp[i-1], v0, v1);
        return res;
    }
}

Node* BDD::restr(int indVar, bool val)
{
    this->getVector()[indVar-1] = val;
    this->setTopNode(res(this->getTopNode(), indVar, val));
    return (this->getTopNode());
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
        if (!val)
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
        std::string s = "[" + this->getOrdervar().at(i)+ ":";
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
        std::vector<int> A = std::vector<int>(this->maxindice);
        for (int i = 0; i < A.size(); i++)
            A[i] = -2;
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
                s = "["+ this->getOrdervar().at(node->getIndice()) +":true;"+str+"]";
                return (s);
            }
            else
            {
                s = "["+ this->getOrdervar().at(node->getIndice()) +":false;"+anysataux(node->getRhs())+"]";
                return (s);
            }
        }
        else
        {
            std::string str = anysataux(node->getRhs());
            if (str != "error")
            {
                s = "["+ this->getOrdervar().at(node->getIndice()) +":false;"+str+"]";
                return (s);
            }
            else
            {
                s = "["+ this->getOrdervar().at(node->getIndice()) +":true;"+anysataux(node->getLhs())+"]";
                return (s);
            }
        }
        return "";
    }
}

size_t pair(size_t i, size_t j)
{
    return ((i+j)*(i+j+1)/2 + i);
}

std::string hash(int i, Node* l, Node* r)
{
    std::ostringstream oss;
    oss << i << l  << r;
    //size_t hash = pair((size_t)(i * 1000000),pair((size_t)l,(size_t)r)) % 15485863;
    return oss.str();
}

Node* BDD::MK(int i, Node* l, Node* r)
{
    if (l == r)
        return l;
    else
    {
        std::string h = hash(i,l,r);
        if (this->vectNode.count(h)==1)
            return this->vectNode.at(h);
        else
        {
            Node* node = new Node(i,l,r);
            this->vectorNode.push_back(node);
            this->vectNode.insert(std::make_pair(h, node));
            return node;
        }
    }
}

size_t calcstring(std::string s)
{
    size_t res = 0;
    for (int i=0; i < s.size(); i++)
    {
        res += (size_t)s[i];
    }
    return (res * 1000000);
}

std::string hashapp(std::string op, Node* u1, Node* u2)
{
    std::ostringstream oss;
    oss << op << u1 << u2;
    return (oss.str());
}

Node* BDD::APP(std::string op, Node* u1, Node* u2)
{
    std::string hash = hashapp(op, u1, u2);
    if (opmap.count(hash)==1)
        return opmap.at(hash);
    else
    {
        Node* node;
        if (u1->isLeaf() && u2->isLeaf())
        {
            if (this->op(op,u1->getValue(),u2->getValue()))
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
            node = this->MK(u1->getIndice(), this->APP(op,u1->getLhs(), u2->getLhs()), this->APP(op,u1->getRhs(), u2->getRhs()));
        }
        else if (u1->getIndice() < u2->getIndice())
        {
            node = this->MK(u1->getIndice(), this->APP(op,u1->getLhs(), u2), this->APP(op,u1->getRhs(), u2));
        }
        else
        {
            node = this->MK(u2->getIndice(), this->APP(op,u1, u2->getLhs()), this->APP(op,u1, u2->getRhs()));
        }
        opmap.insert(std::make_pair(hash, node));
        return node;
    }
}

Node* BDD::APPLY(std::string op, BDD bdd1, BDD bdd2)
{
    Node* u1 = bdd1.getTopNode();
    Node* u2 = bdd2.getTopNode();
    //std::cout << "(" << bdd1.getExpression() << ") " << op << " (" << bdd2.getExpression() << ")" << std::endl;
    this->expression = "( " + bdd1.getExpression() + " ) " + op + " ( " + bdd2.getExpression() + " )";
    Node* node = this->APP(op, u1, u2);
    this->setTopNode(node);
    return node;
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
    if (node != NULL)
        return (pow(2,(node->getIndice() - 1))*count(node));
    return 0;
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
        std::ostringstream oss;
        std::string s = this->getOrdervar().at(node->getIndice());
        oss << s /*<< "(" << node->getIndice() << ")"*/;
        return (oss.str() + "(" + drawbis(node->getLhs())+";"+drawbis(node->getRhs())+")");
    }
}

std::string BDD::getInfoNode(int indice)
{
    if (ordervar.count(indice) >= 1)
        return ordervar.at(indice);
    return "";
}

int getNodeMaxDepth(Node* node, int depth) {
	int ld, rd;
	if (node==NULL) { return depth-1; }
	ld = getNodeMaxDepth(node->getLhs(), depth+1);
	rd = getNodeMaxDepth(node->getRhs(), depth+1);
	return (ld<rd) ? rd : ld;
}

int BDD::getMaxIndice()
{
    return maxindice;
}

Node* BDD::getNodeFalse()
{
    return nodeFalse;
}

Node* BDD::getNodeTrue()
{
    return nodeTrue;
}

std::unordered_map<std::string, int> BDD::getVarorder()
{
    return varorder;
}

std::unordered_map<int, std::string> BDD::getOrdervar()
{
    return ordervar;
}

void BDD::setMaxIndice(int m)
{
    this->maxindice = m;
}

void BDD::setVarorder(std::unordered_map<std::string, int> v)
{
    this->varorder = v;
}

void BDD::setOrdervar(std::unordered_map<int, std::string> o)
{
    this->ordervar = o;
}

void BDD::setVectNode(std::unordered_map<std::string,Node*> v)
{
    this->vectNode = v;
}
void BDD::setVectorNode(std::vector<Node*> v)
{
    this->vectorNode = v;
}

BDD* BDD::andfonc (BDD* bdd1, std::string s)
{
    BDD* bdd = new BDD(bdd1->getNbVar(), bdd1->getVectorNode(), bdd1->getVectNode(), bdd1->getNodeFalse(), bdd1->getNodeTrue(), bdd1->getVarorder(), bdd1->getOrdervar(), bdd1->getMaxIndice(), bdd1->getOpmap());
    bdd->setExpression(s);
    bdd->build();
    if (bdd1->getExpression() == "")
    {
        *bdd1 = *bdd;
    }
    else
    {
        bdd1 = bdd1->transferinfo(bdd, bdd1);
        bdd1->APPLY("&", *bdd1, *bdd);
    }
    return bdd1;
}

BDD* BDD::orfonc (BDD* bdd1, std::string s)
{
    BDD* bdd = new BDD(bdd1->getNbVar(), bdd1->getVectorNode(), bdd1->getVectNode(), bdd1->getNodeFalse(), bdd1->getNodeTrue(), bdd1->getVarorder(), bdd1->getOrdervar(), bdd1->getMaxIndice(), bdd1->getOpmap());
    bdd->setExpression(s);
    bdd->build();
    if (bdd1->getExpression() == "")
    {
        *bdd1 = *bdd;
    }
    else
    {
        bdd1 = bdd1->transferinfo(bdd, bdd1);
        bdd1->APPLY("|", *bdd1, *bdd);
    }
    return bdd1;
}

BDD* BDD::andfonc (BDD* bdd1, BDD* bdd2)
{
    if (bdd1->getExpression() == "")
        return bdd2;
    else if (bdd2->getExpression() == "")
        return bdd1;
    bdd1->APPLY("&", *bdd1, *bdd2);
    return bdd1;
}

BDD* BDD::orfonc (BDD* bdd1, BDD* bdd2)
{
    if (bdd1->getExpression() == "")
        return bdd2;
    else if (bdd2->getExpression() == "")
        return bdd1;
    bdd1->APPLY("|", *bdd1, *bdd2);
    return bdd1;
}

BDD* BDD::implyfonc (BDD* bdd1, std::string s)
{
    BDD* bdd = new BDD(bdd1->getNbVar(), bdd1->getVectorNode(), bdd1->getVectNode(), bdd1->getNodeFalse(), bdd1->getNodeTrue(), bdd1->getVarorder(), bdd1->getOrdervar(), bdd1->getMaxIndice(), bdd1->getOpmap());
    bdd->setExpression(s);
    bdd->build();
    if (bdd1->getExpression() == "")
    {
        *bdd1 = *bdd;
    }
    else
    {
        bdd1->APPLY("=>", *bdd1, *bdd);
    }
    return bdd1;
}

BDD* BDD::implyfonc (BDD* bdd1, BDD* bdd2)
{
    if (bdd1->getExpression() == "")
        return bdd2;
    else if (bdd2->getExpression() == "")
        return bdd1;
    bdd1->APPLY("=>", *bdd1, *bdd2);
    return bdd1;
}

BDD* BDD::transferinfo(BDD* bdd1, BDD* bdd2)
{
    bdd2->setNbVar(bdd1->getNbVar());
    bdd2->setVectorNode(bdd1->getVectorNode());
    bdd2->setVectNode(bdd1->getVectNode());
    bdd2->setVarorder(bdd1->getVarorder());
    bdd2->setOrdervar(bdd1->getOrdervar());
    bdd2->setMaxIndice(bdd1->getMaxIndice());
    bdd2->setOpmap(bdd1->getOpmap());
    return bdd2;
}

std::unordered_map<std::string,Node*> BDD::getOpmap()
{
    return this->opmap;
}

void BDD::setOpmap(std::unordered_map<std::string,Node*> v)
{
    this->opmap = v;
}

Node* getNodeByIndice(Node* node, int i)
{
    if (node->getIndice() == i)
        return node;
    else if (node->isLeaf())
    {
        return NULL;
    }
    else
    {
        Node* n = getNodeByIndice(node->getLhs(), i);
        if (n != NULL)
            return n;
        else
            return getNodeByIndice(node->getRhs(), i);
    }
}

void  BDD::toDot (const std::string& filename)
{
  std::ostringstream path;
  path << filename << ".dot";
  std::ofstream file ( path.str().c_str() );
  toDot (file, this->getTopNode());
  file.close ();
}


void  BDD::toDot (std::ostream& out, Node* node)
{
  out << "digraph BDD {" << std::endl;
  out << "  ratio=1.0;" << std::endl;
  _toDot (out, node);
  out << "}" << std::endl;
}


void  BDD::_toDot (std::ostream& out, Node* node)
{
    int max = this->maxindice + 1;
  if (node == this->nodeFalse) {
    out << "  n" << this->maxindice << " [shape=box,label=\"false\"];" << std::endl;
  } else if (node == this->nodeTrue) {
    out << "  n" << max << " [shape=box,label=\"true\"];" << std::endl;
  } else {
    std::string name = this->ordervar.at(node->getIndice());
    std::ostringstream  nodename;
    nodename << "n" << node->getIndice();

    out << "  " << nodename.str() << " [label=\"\\N\\n" << name << "\",fontname=\"Bitstream Vera Sans\"];" << std::endl;
    out << "  " << nodename.str() << " -> " << "n";
    if (node->getLhs()->isLeaf() && node->getLhs()->getValue())
        out << max;
    else if (node->getLhs()->isLeaf() && !node->getLhs()->getValue())
        out << this->maxindice;
    else
        out << node->getLhs()->getIndice();
    out << "[label=\"H\",color=green]" << ";" << std::endl;
    out << "  " << nodename.str() << " -> " << "n";
    if (node->getRhs()->isLeaf() && node->getRhs()->getValue())
        out << max;
    else if (node->getRhs()->isLeaf() && !node->getRhs()->getValue())
        out << this->maxindice;
    else
        out << node->getRhs()->getIndice();
    out << "[label=\"L\",color=red]" << ";" << std::endl;

    _toDot(out, node->getLhs());
    _toDot(out, node->getRhs());
  }
}

BDD* BDD::T(int ind, int i, int j)
{
    Node* node = MK(ind+1, this->nodeTrue, this->nodeFalse);
    if (ordervar.count(ind) == 0)
    {
        std::ostringstream oss;
        oss << "c" << i << j;
        ordervar.insert(std::make_pair(ind+1, oss.str()));
        varorder.insert(std::make_pair(oss.str(), ind+1));
    }
    this->setTopNode(node);
    this->expression = ordervar.at(ind+1);
    this->maxindice = 2;
    return this;
}

void BDD::exist(std::string var)
{
    if(varorder.count(var) == 1)
    {
        int indicevar = varorder.at(var);
        existbis(this->topNode, indicevar);
    }
    else
    {
        std::cerr << "Pas de variable avec le nom " << var << std::endl;
    }
}

void BDD::exist(std::vector<std::string> tab)
{
    for (int i = 0; i < tab.size(); i++)
    {
        exist(tab[i]);
        //std::cout << tab[i] << " draw : " << this->draw() << std::endl;
    }
}

void BDD::exist(int indicevar)
{
    if(ordervar.count(indicevar) == 1)
    {
        existbis(this->topNode, indicevar);
    }
    else
    {
        std::cerr << "Pas de variable avec ce numéro" << std::endl;
    }
}

std::string BDD::suppocc(std::vector<std::string> tab, int indice)
{
    std::string s = this->ordervar.at(indice);
    std::string res = "";
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
                    c = c + 1;
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
                    c = c + 2;
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
                    c = c + 1;
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
                    c = c + 2;
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
                }
            }
        }
    }
    for (int i = 0; i < tab.size(); i++)
    {
        if (tab[i] == s)
        {
            /*if (res != "")
                res = res + " ";
            std::string strval = "";
            if (val)
                strval = "true";
            else
                strval = "false";
            res = res + strval;*/
            if (i+1 < tab.size() && (tab[i+1] == "&" || tab[i+1] == "|" || tab[i+1] == "xor" || tab[i+1] == "=>" || tab[i+1] == "<=>"))
            {
                std::vector<std::string>::iterator it;
                it = tab.begin();
                if (i-1 > 0 && tab[i-1] == "!")
                {
                    tab.erase(it+i+1);
                    tab.erase(it+i);
                    tab.erase(it+i-1);
                    i = i - 2;
                }
                else
                {
                    tab.erase(it+i+1);
                    tab.erase(it+i);
                    i = i - 1;
                }
            }
            else if (i+1 < tab.size() && (tab[i+1] == ")") && i-1 >= 0 && tab[i-1] == "(")
            {
                std::vector<std::string>::iterator it;
                it = tab.begin();
                tab.erase(it+i+1);
                tab.erase(it+i);
                tab.erase(it+i-1);
                i = i - 2;
            }
            else if (i-1 >= 0 && (tab[i-1] == "&" || tab[i-1] == "|" || tab[i-1] == "xor" || tab[i-1] == "=>" || tab[i-1] == "<=>"))
            {
                std::vector<std::string>::iterator it;
                it = tab.begin();
                tab.erase(it+i);
                tab.erase(it+i-1);
                i = i - 2;
            }
            else
            {
                std::vector<std::string>::iterator it;
                it = tab.begin();
                tab.erase(it+i);
                i = i - 1;
            }
        }
        else if ((tab[i] == "&" || tab[i] == "|" || tab[i] == "xor" || tab[i] == "=>" || tab[i] == "<=>") && i+1 < tab.size() && tab[i+1] == "(" && i+2 < tab.size() && tab[i+2] == s)
        {
            if (i+3 < tab.size() && (tab[i+3] == ")"))
            {
                std::vector<std::string>::iterator it;
                it = tab.begin();
                if (i-1 >= 0 && (tab[i-1] == "&" || tab[i-1] == "|" || tab[i-1] == "xor" || tab[i-1] == "=>" || tab[i-1] == "<=>"))
                {
                    tab.erase(it+i-1, it+i+4);
                }
                else if (i+4 < tab.size() && (tab[i+4] == "&" || tab[i+4] == "|" || tab[i+4] == "xor" || tab[i+4] == "=>" || tab[i+4] == "<=>"))
                {
                    tab.erase(it+i, it+i+5);
                }
            }
        }
        else if (tab[i] == "(" && i+1 < tab.size() && tab[i+1] == s)
        {
            if (i+2 < tab.size() && (tab[i+2] == ")"))
            {
                std::vector<std::string>::iterator it;
                it = tab.begin();
                if (i-1 >= 0 && (tab[i-1] == "&" || tab[i-1] == "|" || tab[i-1] == "xor" || tab[i-1] == "=>" || tab[i-1] == "<=>"))
                {
                    tab.erase(it+i-1, it+i+3);
                    i = i - 2;
                }
                else if (i+3 < tab.size() && (tab[i+3] == "&" || tab[i+3] == "|" || tab[i+3] == "xor" || tab[i+3] == "=>" || tab[i+3] == "<=>"))
                {
                    tab.erase(it+i, it+i+4);
                }
            }
        }
        else
        {
            if (res != "")
                res = res + " ";
            res = res + tab[i];
        }
    }
    return res;
}

Node* BDD::existbis(Node* node, int indice)
{
    /*Node* n1 = res(node, indice, true);
    Node* n2 = res(node, indice, false);*/
    BDD bdd1 = *this;
    BDD bdd2 = *this;
    bdd1.setExpression("");
    bdd2.setExpression("");
    /*std::vector<std::string> tab = parse(this->getExpression());
    std::cout << "taille de tab : " << tab.size() << std::endl;
    std::string newexpr = suppocc(tab, indice);
    bdd1.setExpression(newexpr);
    bdd2.setExpression(newexpr);*/
    //std::cout << "before restrict exist pour indice " << indice << std::endl;
    bdd1.restr(indice, true);
    bdd2.restr(indice, false);
    //std::cout << "after restrict exist pour indice " << indice << std::endl;
    //bdd1->build();
    //bdd2->build();
    //bdd1->setTopNode(n1);
    //bdd2->setTopNode(n2);
    //bdd1->setExpression(this->getExpression());
    //bdd2->setExpression(this->getExpression());
    //std::cout << "before apply exist pour indice " << indice << std::endl;
    this->APPLY("|", bdd1, bdd2);
    //std::cout << "after apply exist pour indice " << indice << std::endl;
    //this->setExpression(bdd1.getExpression());
    return this->topNode;
    /*if (node->getIndice() > indice)
    {
        return node;
    }
    else if (node->getIndice() < indice)
    {
        return MK(node->getIndice(), existbis(node->getLhs(), indice), existbis(node->getRhs(), indice));
    }
    else
    {
        Node* n1 = res(node->getLhs(), indice, true);
        Node* n2 = res(node->getRhs(), indice, false);
        BDD* bdd1 = new BDD(this->getNbVar(), this->getVectorNode(), this->getVectNode(), this->getNodeFalse(), this->getNodeTrue(), this->getVarorder(), this->getOrdervar(), this->getMaxIndice(), this->getOpmap());
        BDD* bdd2 = new BDD(this->getNbVar(), this->getVectorNode(), this->getVectNode(), this->getNodeFalse(), this->getNodeTrue(), this->getVarorder(), this->getOrdervar(), this->getMaxIndice(), this->getOpmap());
        std::vector<std::string> tab = parse(this->getExpression());
        this->setExpression(suppocc(tab, indice));
        bdd1->setTopNode(n1);
        bdd2->setTopNode(n2);
        bdd1->setExpression(this->getExpression());
        bdd2->setExpression(this->getExpression());
        APPLY("|", *bdd1, *bdd2);
        this->setExpression(bdd1->getExpression());
        return this->topNode;
    }*/
}

void BDD::notfonc(BDD* bdd)
{
    bdd->setTopNode(bdd->notfoncbis(bdd->getTopNode()));
}



Node* BDD::notfoncbis(Node* node)
{
    Node* n1;
    Node* n2;
    if (node->getLhs() == this->nodeFalse)
        n1 = this->nodeTrue;
    else if (node->getLhs() == this->nodeTrue)
        n1 = this->nodeFalse;
    else
        n1 = this->notfoncbis(node->getLhs());
    if (node->getRhs() == this->nodeFalse)
        n2 = this->nodeTrue;
    else if (node->getRhs() == this->nodeTrue)
        n2 = this->nodeFalse;
    else
        n2 = this->notfoncbis(node->getRhs());
    return MK(node->getIndice(), n1, n2);
}

void BDD::composition(BDD* bdd, std::string var)
{
    if(varorder.count(var) == 1)
    {
        int indicevar = varorder.at(var);
        compositionbis(bdd, this->topNode, indicevar);
    }
    else
    {
        std::cerr << "Pas de variable avec le nom " << var << std::endl;
    }
}

void BDD::composition(BDD* bdd, int indicevar)
{
    if(ordervar.count(indicevar) == 1)
    {
        compositionbis(bdd, this->topNode, indicevar);
    }
    else
    {
        std::cerr << "Pas de variable avec ce numéro" << std::endl;
    }
}

Node* BDD::compositionbis(BDD* bdd, Node* node, int indice)
{
    if (node->getIndice() > indice)
    {
        return node;
    }
    else if (node->getIndice() < indice)
    {
        return MK(node->getIndice(), compositionbis(bdd, node->getLhs(), indice), compositionbis(bdd, node->getRhs(), indice));
    }
    else
    {
        Node* n1 = res(node->getLhs(), indice, true);
        Node* n2 = res(node->getRhs(), indice, false);
        BDD* bdd1 = new BDD(this->getNbVar(), this->getVectorNode(), this->getVectNode(), this->getNodeFalse(), this->getNodeTrue(), this->getVarorder(), this->getOrdervar(), this->getMaxIndice(), this->getOpmap());
        BDD* bdd2 = new BDD(this->getNbVar(), this->getVectorNode(), this->getVectNode(), this->getNodeFalse(), this->getNodeTrue(), this->getVarorder(), this->getOrdervar(), this->getMaxIndice(), this->getOpmap());
        bdd1->setTopNode(n1);
        bdd2->setTopNode(n2);
        BDD* bdd3 = new BDD(bdd->getNbVar(), bdd->getVectorNode(), bdd->getVectNode(), bdd->getNodeFalse(), bdd->getNodeTrue(), bdd->getVarorder(), bdd->getOrdervar(), bdd->getMaxIndice(), bdd->getOpmap());
        bdd3->setTopNode(bdd->getTopNode());
        bdd3->notfonc(bdd3);
        bdd1->APPLY("&", *bdd1, *bdd);
        bdd2->APPLY("&", *bdd2, *bdd3);
        APPLY("|", *bdd1, *bdd2);
        return this->topNode;
    }
}

void BDD::rename(std::vector<std::string> v)
{
    int number = this->maxindice;
    for (int count =0; count < v.size(); count++)
    {
        std::string s = v[count];
        std::string sprime = s.substr(0, s.size()-1);
        if (varorder.count(sprime) != 1)
        {
            int indVar = varorder.at(s);
            varorder.erase(s);
            ordervar.erase(indVar);
            varorder.insert(std::make_pair(s, number));
            varorder.insert(std::make_pair(sprime, indVar));
            ordervar.insert(std::make_pair(number, s));
            ordervar.insert(std::make_pair(indVar, sprime));
            number++;
        }
    }
    this->maxindice = number;
    this->vect = std::vector<bool>(number-1);
    this->nodeFalse->setIndice(number);
    this->nodeTrue->setIndice(number);
    this->renamebis(v, this->getTopNode());
}

Node* BDD::renamebis(std::vector<std::string> v, Node* n)
{
    if (n->isLeaf())
        return n;
    std::string s = this->ordervar.at(n->getIndice());
    if (std::find(v.begin(), v.end(), s) != v.end())
    {
        std::string sprime = s.substr(0, s.size()-1);
        n->setIndice(varorder.at(sprime));
    }
    return MK(n->getIndice(), renamebis(v, n->getLhs()), renamebis(v, n->getRhs()));
}
