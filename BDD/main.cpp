#include <iostream>
#include "include/Node.h"
#include "include/BDD.h"

using namespace std;

int main()
{
    Node* node = new Node();
    BDD* bdd = new BDD();
    bdd->setExpression("(a | b & c) => (d xor e) && f");
    std::cout << "Expression : " << bdd->getExpression() << std::endl;
    bdd->setNbVar(6);
    node = bdd->build();
    cout << "Nombre de solution satisfaisante pour bdd: " << bdd->satcount() << endl;
    cout << "Une solution : " << bdd->anysat() << endl;
    Node* node2 = new Node();
    BDD* bdd2 = new BDD();
    bdd2->setExpression("a & b | c");
    std::cout << "Expression : " << bdd2->getExpression() << std::endl;
    bdd2->setNbVar(3);
    node2 = bdd2->build();
    int res = bdd->satcount();
    cout << "Nombre de solution satisfaisante pour bdd: " << res << endl;
    cout << "Draw pour bdd: (" << bdd->draw() << ")" << endl;
    cout << "Nombre de solution satisfaisante pour bdd2: " << bdd2->satcount() << endl;
    cout << "Draw pour bdd2: (" << bdd2->draw() << ")" << endl;
    BDD* bdd3 = new BDD();
    Node* node3 = bdd3->APPLY("&",*bdd, *bdd2);
    cout << "Nombre de solution satisfaisante pour apply: " << bdd3->satcount() << endl;
    cout << "Draw pour apply: (" << bdd3->draw() << ")" << endl;
    BDD* bdd4 = bdd3;
    std::cout << "Expression : " << bdd4->getExpression() << std::endl;
    Node* node4 = bdd4->build();
    cout << "Nombre de solution satisfaisante pour bdd4: " << bdd4->satcount() << endl;
    cout << "Draw pour bdd4: (" << bdd4->draw() << ")" << endl;
    cout << bdd4->anysat() << endl;
    Node* node5 = bdd4->restr(1, true);
    BDD* bdd5 = bdd4;
    bdd5->setTopNode(node5);
    bdd5->build();
    cout << "Nombre de solution satisfaisante pour bdd5: " << bdd5->satcount() << endl;
    cout << "Draw pour bdd5: (" << bdd5->draw() << ")" << endl;
    bdd5->allsat();
    //bdd->DrawTree_Horizonral(node,'r',0,0,0);
    return 0;
}
