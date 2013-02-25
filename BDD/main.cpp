#include <iostream>
#include "include/Node.h"
#include "include/BDD.h"

using namespace std;

int main()
{
    Node* node = new Node();
    BDD* bdd = new BDD();
    bdd->setExpression("a & b | c");
    std::cout << "Expression : " << bdd->getExpression() << std::endl;
    bdd->setNbVar(3);
    node = bdd->build();
    Node* node2 = new Node();
    BDD* bdd2 = new BDD();
    bdd2->setExpression("a & b");
    std::cout << "Expression : " << bdd2->getExpression() << std::endl;
    bdd2->setNbVar(2);
    node2 = bdd2->build();
    //Node* node3 = bdd->APPLY("&",bdd, bdd2);
    int res = bdd->satcount();
    cout << "Nombre de solution satisfaisante pour bdd: " << res << endl;
    cout << "Nombre de solution satisfaisante pour bdd2: " << bdd2->satcount() << endl;
    //bdd->DrawTree_Horizonral(node,'r',0,0,0);
    std::cout << "(" << bdd->draw() << ")" << std::endl;
    return 0;
}
