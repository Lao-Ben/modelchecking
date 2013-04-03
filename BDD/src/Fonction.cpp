#include "../include/Fonction.h"

using namespace std;

Fonction::Fonction(int n)
{
    this->size = n;
}

Fonction::~Fonction()
{

}

int Fonction::getSize()
{
    return this->size;
}

void Fonction::setSize(int n)
{
    this->size = n;
}

int Fonction::queen()
{
    int n = this->size;
    std::ostringstream namefich;
    BDD* bdd = new BDD();
    bdd->setNbVar(n*n);
    // créer un flux de sortie
    std::ostringstream oss;
    namefich << "test.txt";
    std::string namefichstr = namefich.str();
    std::ofstream fichier(namefichstr, ios::out | ios::trunc);
    namefich.str("");
    namefich.clear();
    BDD* bdd1 = new BDD(bdd->getNbVar(), bdd->getVectorNode(), bdd->getVectNode(), bdd->getNodeFalse(), bdd->getNodeTrue(), bdd->getVarorder(), bdd->getOrdervar(), bdd->getMaxIndice(), bdd->getOpmap());
    BDD* bddtemp1;
    for (int i=0; i < n; i++)
    {
        bddtemp1 = new BDD(bdd1->getNbVar(), bdd1->getVectorNode(), bdd1->getVectNode(), bdd1->getNodeFalse(), bdd1->getNodeTrue(), bdd1->getVarorder(), bdd1->getOrdervar(), bdd1->getMaxIndice(), bdd1->getOpmap());
        for (int j=0; j < n; j++)
        {
            oss << "( c"<<i<<j<<" & ";
            bool first = true;
            for (int h = 0; h < n; h++)
            {
                if (h != j)
                {
                    if (!first)
                        oss << " & ";
                    oss << "!c"<<i<<h;
                    first = false;
                }
            }
            oss << " )";
            bddtemp1 = bddtemp1->orfonc(bddtemp1, oss.str());
            oss.str("");
            oss.clear();
        }
        bdd1 = bdd1->andfonc(bdd1, bddtemp1);
        bdd1 = bdd1->transferinfo(bddtemp1, bdd1);
        oss.str("");
        oss.clear();
    }
    std::cout << "fin premier bdd" << std::endl;
    /*oss << " & ";*/
    BDD* bdd2 = new BDD(bdd1->getNbVar(), bdd1->getVectorNode(), bdd1->getVectNode(), bdd1->getNodeFalse(), bdd1->getNodeTrue(), bdd1->getVarorder(), bdd1->getOrdervar(), bdd1->getMaxIndice(), bdd1->getOpmap());
    BDD* bddtemp2;
    for (int i=0; i < n; i++)
    {
        bddtemp2 = new BDD(bdd2->getNbVar(), bdd2->getVectorNode(), bdd2->getVectNode(), bdd2->getNodeFalse(), bdd2->getNodeTrue(), bdd2->getVarorder(), bdd2->getOrdervar(), bdd2->getMaxIndice(), bdd2->getOpmap());
        for (int j=0; j < n; j++)
        {
            oss << "( c"<<j<<i<<" & ";
            bool first = true;
            for (int h = 0; h < n; h++)
            {
                if (h != j)
                {
                    if (!first)
                        oss << " & ";
                    oss << "!c"<<h<<i;
                    first = false;
                }
            }
            oss << " )";
            bddtemp2 = bddtemp2->orfonc(bddtemp2, oss.str());
            oss.str("");
            oss.clear();
        }
        bdd2 = bdd2->andfonc(bdd2, bddtemp2);
        bdd2 = bdd2->transferinfo(bddtemp2, bdd2);
        oss.str("");
        oss.clear();
    }
    std::cout << "fin second bdd" << std::endl;
    /*oss << " & ";*/
    BDD* bdd3 = new BDD(bdd2->getNbVar(), bdd2->getVectorNode(), bdd2->getVectNode(), bdd2->getNodeFalse(), bdd2->getNodeTrue(), bdd2->getVarorder(), bdd2->getOrdervar(), bdd2->getMaxIndice(), bdd2->getOpmap());
    BDD* bddtemp3;
    for (int i = 0; i < n; i++)
    {
        bddtemp3 = new BDD(bdd3->getNbVar(), bdd3->getVectorNode(), bdd3->getVectNode(), bdd3->getNodeFalse(), bdd3->getNodeTrue(), bdd3->getVarorder(), bdd3->getOrdervar(), bdd3->getMaxIndice(), bdd3->getOpmap());
        for (int j=0; j < n; j++)
        {
            oss << "( c"<<i<<j;
            std::ostringstream osstemp;
            for (int h = 0; h < n; h++)
            {
                int val = j+h-i;
                if (h != i && val>=0 && val<n)
                {
                    osstemp <<" & ";
                    osstemp << "!c"<<h<<val;
                }
            }
            std::string temp = osstemp.str();
            oss << temp << " )";
            bddtemp3 = bddtemp3->orfonc(bddtemp3, oss.str());
            oss.str("");
            oss.clear();
        }
        bdd3 = bdd3->andfonc(bdd3, bddtemp3);
        bdd3 = bdd3->transferinfo(bddtemp3, bdd3);
        oss.str("");
        oss.clear();
    }
    std::cout << "fin troisième bdd" << std::endl;
    /*oss << " & ";*/
    BDD* bdd4 = new BDD(bdd3->getNbVar(), bdd3->getVectorNode(), bdd3->getVectNode(), bdd3->getNodeFalse(), bdd3->getNodeTrue(), bdd3->getVarorder(), bdd3->getOrdervar(), bdd3->getMaxIndice(), bdd3->getOpmap());
    BDD* bddtemp4;
    for (int i = 0; i < n; i++)
    {
        bddtemp4 = new BDD(bdd4->getNbVar(), bdd4->getVectorNode(), bdd4->getVectNode(), bdd4->getNodeFalse(), bdd4->getNodeTrue(), bdd4->getVarorder(), bdd4->getOrdervar(), bdd4->getMaxIndice(), bdd4->getOpmap());
        for (int j=0; j < n; j++)
        {
            oss << "( c"<<i<<j;
            std::ostringstream osstemp;
            for (int h = 0; h < n; h++)
            {
                int val = j+i-h;
                if (h != i && val>=0 && val<n)
                {
                    osstemp <<" & ";
                    osstemp << "!c"<<h<<val;
                }
            }
            std::string temp = osstemp.str();
            oss << temp << " )";
            bddtemp4 = bddtemp4->orfonc(bddtemp4, oss.str());
            oss.str("");
            oss.clear();
        }
        bdd4 = bdd4->andfonc(bdd4, bddtemp4);
        bdd4 = bdd4->transferinfo(bddtemp4, bdd4);
        oss.str("");
        oss.clear();
    }
    std::cout << "fin quatrième bdd" << std::endl;
    bdd = bdd->andfonc(bdd, bdd1);
    std::cout << "fin apply1" << std::endl;
    bdd = bdd->andfonc(bdd, bdd2);
    std::cout << "fin apply2" << std::endl;
    bdd = bdd->andfonc(bdd, bdd3);
    std::cout << "fin apply3" << std::endl;
    bdd = bdd->andfonc(bdd, bdd4);
    std::cout << "fin apply4" << std::endl;
    //std::cout << "apply : " << bdd->getExpression() << std::endl << bdd-> () << std::endl << std::endl;
    /*cout << "apply : " << bdd->getExpression() << std::endl << bdd->draw() << std::endl << std::endl;
    fichier << "apply : " << bdd->getExpression() << std::endl << bdd->draw() << std::endl << std::endl;*/
    // récupérer une chaîne de caractères
    std::string s = oss.str();
    Node* node = new Node();
    //bdd->setExpression("( "+s+" )");
    /*bdd = bdd->andfonc(bdd, std::string("( a & ( b & c ) )"));
    bdd = bdd->orfonc(bdd, std::string("b & c"));
    bdd = bdd->andfonc(bdd, bdd->getExpression());*/
    //std::cout << "Expression : " << bdd->getExpression() << std::endl;

    cout << "Debut build"<<endl;
    //bdd->testeval("c00", false);
    //node = bdd->build();
    cout << "Fin build"<<endl;
    fichier << "Nombre de solution satisfaisante pour bdd: " << bdd->satcount() << endl;
    cout << "Nombre de solution satisfaisante pour bdd: " << bdd->satcount() << endl;
    fichier << "Une solution : " << bdd->anysat() << endl;
    cout << "Une solution : " << bdd->anysat() << endl;
    //cout << bdd->draw() << endl << endl;
    fichier << endl << endl;
    //bdd->allsat();
    std::ostringstream namefichgraph;
    namefichgraph << "graph";
    bdd->toDot(namefichgraph.str());
    return 0;
}

BDD* B(BDD* bdd, int x, int y, int n)
{
    return bdd->T(x * n + y, x, y);
}

BDD* transition(BDD* bdd, int x, int y, int n, std::unordered_map<std::string, std::pair<int, int> >* map, std::vector<std::string>* vect, std::vector<std::string>* vectprime)
{
    std::string res = "";
    if (x >= 0 && x < n &&
            y >= 0 && y < n)
    {
        std::ostringstream temp;
        temp << "c" << x <<  y;
        if ((*map).count(temp.str()) != 1)
        {
            (*vect).push_back(temp.str());
            (*map).insert(std::make_pair(temp.str(), std::make_pair(x, y)));
        }
        temp << "'";
        res = temp.str();
        (*vectprime).push_back(temp.str());
        bdd = bdd->orfonc(bdd, res);
    }
    return bdd;
}

int Fonction::knight()
{
    int n = this->size;
    bool isvalid = false;
    /*for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {*/
            BDD* pb = new BDD();
            pb->setNbVar(2*n*n);
            B(pb, 0, 0, n);
            BDD* pb1 = new BDD();
            pb1->setExpression("");
            pb1->setTopNode(NULL);
            std::unordered_map<std::string, std::pair<int, int> > map;
            std::vector<std::string> vect;
            std::ostringstream varname;
            varname << "c" << 0 << 0;
            vect.push_back(varname.str());
            map.insert(std::make_pair(varname.str(), std::make_pair(0, 0)));
            int count = 1;
            std::string spb = pb->draw();
            std::string spb1 = pb1->draw();
            while (pb->getMaxIndice()-1 != (2*n*n))
            {
                std::cout << "iter : " << count << std::endl;
                count++;
                std::vector<std::string> vectprime;
                std::ostringstream trans;
                int size = vect.size();
                std::vector<std::string> vecttemp = vect;
                BDD* bdd = new BDD(pb->getNbVar(), pb->getVectorNode(), pb->getVectNode(), pb->getNodeFalse(), pb->getNodeTrue(), pb->getVarorder(), pb->getOrdervar(), pb->getMaxIndice(), pb->getOpmap());
                for (int h = 0; h < size; h++)
                {
                    if (trans.str() != "")
                        trans << " | ";
                    std::pair<int, int> pair = map.at(vect[h]);
                    int i = pair.first;
                    int j = pair.second;
                    std::ostringstream tmp;
                    tmp << "c" << i << j;
                    std::ostringstream temp;
                    std::string s = "";
                    std::string sold = "";
                    BDD* bddtemp4 = new BDD(bdd->getNbVar(), bdd->getVectorNode(), bdd->getVectNode(), bdd->getNodeFalse(), bdd->getNodeTrue(), bdd->getVarorder(), bdd->getOrdervar(), bdd->getMaxIndice(), bdd->getOpmap());
                    bddtemp4 = transition(bddtemp4, i - 2, j - 1, n, &map, &vect, &vectprime);
                    bddtemp4 = transition(bddtemp4, i - 2, j + 1, n, &map, &vect, &vectprime );
                    bddtemp4 = transition(bddtemp4, i - 1, j - 2, n, &map, &vect, &vectprime);
                    bddtemp4 = transition(bddtemp4, i - 1, j + 2, n, &map, &vect, &vectprime);
                    bddtemp4 = transition(bddtemp4, i + 1, j - 2, n, &map, &vect, &vectprime);
                    bddtemp4 = transition(bddtemp4, i + 1, j + 2, n, &map, &vect, &vectprime);
                    bddtemp4 = transition(bddtemp4, i + 2, j - 1, n, &map, &vect, &vectprime);
                    bddtemp4 = transition(bddtemp4, i + 2, j + 1, n, &map, &vect, &vectprime);
                    bddtemp4 = bddtemp4->andfonc(bddtemp4, tmp.str());
                    bdd = bdd->orfonc(bdd, bddtemp4);
                    bdd = bdd->transferinfo(bddtemp4, bdd);
                    //std::cout << "bdd : " << bdd->draw() << std::endl;
                    tmp << temp.str() << " ) )";
                    trans << tmp.str();
                }
                //std::cout << bdd->getExpression() << std::endl;
                free(pb1);
                pb1 = new BDD(*pb);
                BDD tmpbdd = *pb;
                pb1 = pb1->andfonc(bdd, &tmpbdd);
                pb1 = pb1->transferinfo(bdd, pb1);
                //std::cout << "after and" << std::endl;
                pb1->exist(vecttemp);
                //std::cout << "after exist : " << pb1->draw() << std::endl;
                //std::cout << pb1->getExpression() << std::endl;
                pb1->rename(vectprime);
                pb1 = pb1->orfonc(pb1, pb);
                pb = pb->transferinfo(pb1, pb);
                //std::cout << "after or" << std::endl;
                spb = pb->draw();
                spb1 = pb1->draw();
                //std::cout << spb << std::endl;
                //std::cout << spb1 << std::endl;
                if (spb == spb1)
                    break;
                free(pb);
                pb = new BDD(*pb1);
                //std::cout << pb->getTopNode() << std::endl;
            }
            if ((pb->getMaxIndice()-1) == (2*n*n))
            {
                isvalid = true;
            }
            free(pb);
            free(pb1);
        /*}
        if (isvalid)
            break;
    }*/
    if (isvalid)
        std::cout << "Bravo vous avez réussit !" << std::endl;
    else
        std::cout << "Désolé vous avez un point fixe !" << std::endl;
    /*cout << "expression: " << pb->getExpression() << endl;
    cout << "Nombre de solution satisfaisante pour pb: " << pb->satcount() << endl;
    cout << "apply : " << pb->draw() << std::endl << std::endl;
    cout << "Une solution : " << pb->anysat() << endl;*/
    //pb->allsat();
    return 0;
}
