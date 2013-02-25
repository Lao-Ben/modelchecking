#include <iostream>
#include "include/Node.h"
#include "include/BDD.h"

using namespace std;

int main()
{
    Node* node = new Node();
    BDD* bdd = new BDD();
    bdd->setExpression("(a & b) => (c || b)");
    std::cout << "Expression : " << bdd->getExpression() << std::endl;
    bdd->setNbVar(3);
    node = bdd->build();
    int res = bdd->satcount(node);
    cout << "Nombre de solution satisfaisante: " << res << endl;
    return 0;
}
