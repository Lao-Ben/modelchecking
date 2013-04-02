#include <iostream>
#include <fstream>
#include "include/Fonction.h"

using namespace std;

int main()
{
    Fonction* f = new Fonction(4);
    //f->queen();
    /*BDD* bdd = new BDD();
    bdd->setNbVar(6);
    bdd->setExpression("( a | b ) & ( a & ( c | d ) | b & ( e | f ) )");
    bdd->build();
    std::cout << bdd->getExpression() << std::endl;
    std::cout << bdd->draw() << std::endl;
    std::cout << bdd->satcount() << std::endl;
    bdd->setExpression("a & ( c | d ) | b & ( e | f )");
    bdd->build();
    std::cout << bdd->getExpression() << std::endl;
    std::cout << bdd->draw() << std::endl;
    std::cout << bdd->satcount() << std::endl;*/
    /*std::vector<string> vect;
    vect.push_back("a");
    vect.push_back("c");
    bdd->exist(vect);
    std::cout << bdd->draw() << std::endl;*/
    /*BDD* bdd3 = new BDD(bdd->getNbVar(), bdd->getVectVar(), bdd->getVectorNode(), bdd->getVectNode(), bdd->getNodeFalse(), bdd->getNodeTrue(), bdd->getVarorder(), bdd->getOrdervar(), bdd->getMaxIndice(), bdd->getOpmap());
    bdd3->setTopNode(bdd->getTopNode());
    bdd3->notfonc(bdd3);
    std::cout << bdd->draw() << std::endl;
    std::cout << bdd3->draw() << std::endl;*/
    f->knight();
    return 0;
}
