#include <iostream>
#include <fstream>
#include "include/Node.h"
#include "include/BDD.h"

using namespace std;

int main()
{
    int n  = 8;
    std::ostringstream namefich;
    BDD* bdd = new BDD();
    bdd->setNbVar(n*n);
    int pos = 0;
    // créer un flux de sortie
    std::ostringstream oss;
    namefich << "test" << pos << ".txt";
    std::string namefichstr = namefich.str();
    std::ofstream fichier(namefichstr, ios::out | ios::trunc);
    namefich.str("");
    namefich.clear();
    BDD* bdd1 = new BDD(bdd->getNbVar(), bdd->getVectVar(), bdd->getVectorNode(), bdd->getVectNode(), bdd->getNodeFalse(), bdd->getNodeTrue(), bdd->getVarorder(), bdd->getOrdervar(), bdd->getMaxIndice(), bdd->getOpmap());
    BDD* bddtemp1;
    for (int i=0; i < n; i++)
    {
        bddtemp1 = new BDD(bdd1->getNbVar(), bdd1->getVectVar(), bdd1->getVectorNode(), bdd1->getVectNode(), bdd1->getNodeFalse(), bdd1->getNodeTrue(), bdd1->getVarorder(), bdd1->getOrdervar(), bdd1->getMaxIndice(), bdd1->getOpmap());
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
    BDD* bdd2 = new BDD(bdd1->getNbVar(), bdd1->getVectVar(), bdd1->getVectorNode(), bdd1->getVectNode(), bdd1->getNodeFalse(), bdd1->getNodeTrue(), bdd1->getVarorder(), bdd1->getOrdervar(), bdd1->getMaxIndice(), bdd1->getOpmap());
    BDD* bddtemp2;
    for (int i=0; i < n; i++)
    {
        bddtemp2 = new BDD(bdd2->getNbVar(), bdd2->getVectVar(), bdd2->getVectorNode(), bdd2->getVectNode(), bdd2->getNodeFalse(), bdd2->getNodeTrue(), bdd2->getVarorder(), bdd2->getOrdervar(), bdd2->getMaxIndice(), bdd2->getOpmap());
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
    BDD* bdd3 = new BDD(bdd2->getNbVar(), bdd2->getVectVar(), bdd2->getVectorNode(), bdd2->getVectNode(), bdd2->getNodeFalse(), bdd2->getNodeTrue(), bdd2->getVarorder(), bdd2->getOrdervar(), bdd2->getMaxIndice(), bdd2->getOpmap());
    BDD* bddtemp3;
    for (int i = 0; i < n; i++)
    {
        bddtemp3 = new BDD(bdd3->getNbVar(), bdd3->getVectVar(), bdd3->getVectorNode(), bdd3->getVectNode(), bdd3->getNodeFalse(), bdd3->getNodeTrue(), bdd3->getVarorder(), bdd3->getOrdervar(), bdd3->getMaxIndice(), bdd3->getOpmap());
        for (int j=0; j < n; j++)
        {
            oss << "( c"<<i<<j;
            std::ostringstream osstemp;
            bool first = true;
            for (int h = 0; h < n; h++)
            {
                int val = j+h-i;
                if (h != i && val>=0 && val<n)
                {
                    if (first)
                        osstemp <<" & ( ";
                    if (!first)
                        osstemp << " & ";
                    osstemp << "!c"<<h<<val;
                    first = false;
                }
            }
            std::string temp = osstemp.str();
            if (temp != "")
                oss << temp << " ) )";
            else
                oss << " )";
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
    BDD* bdd4 = new BDD(bdd3->getNbVar(), bdd3->getVectVar(), bdd3->getVectorNode(), bdd3->getVectNode(), bdd3->getNodeFalse(), bdd3->getNodeTrue(), bdd3->getVarorder(), bdd3->getOrdervar(), bdd3->getMaxIndice(), bdd3->getOpmap());
    BDD* bddtemp4;
    for (int i = 0; i < n; i++)
    {
        bddtemp4 = new BDD(bdd4->getNbVar(), bdd4->getVectVar(), bdd4->getVectorNode(), bdd4->getVectNode(), bdd4->getNodeFalse(), bdd4->getNodeTrue(), bdd4->getVarorder(), bdd4->getOrdervar(), bdd4->getMaxIndice(), bdd4->getOpmap());
        for (int j=0; j < n; j++)
        {
            oss << "( c"<<i<<j;
            std::ostringstream osstemp;
            bool first = true;
            for (int h = 0; h < n; h++)
            {
                int val = j+i-h;
                if (h != i && val>=0 && val<n)
                {
                    if (first)
                        osstemp <<" & ( ";
                    if (!first)
                        osstemp << " & ";
                    osstemp << "!c"<<h<<val;
                    first = false;
                }
            }
            std::string temp = osstemp.str();
            if (temp != "")
                oss << temp << " ) )";
            else
                oss << " )";
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
    cout << "apply : " << bdd->getExpression() << std::endl << bdd->draw() << std::endl << std::endl;
    fichier << "apply : " << bdd->getExpression() << std::endl << bdd->draw() << std::endl << std::endl;
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
    bdd->toDot("graph");
    return 0;
}
