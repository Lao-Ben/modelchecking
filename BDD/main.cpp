#include <iostream>
#include <fstream>
#include "include/Queens.h"
#include "include/Knight.h"
#include "include/GraphColoring.h"

using namespace std;

int main(int argc, char *argv[])
{
    //f->queen();
    /*BDD* bdd = new BDD();
    bdd->setNbVar(6);
    bdd->setExpression("( a | b ) & ( a & ( c | d ) | b & ( e | f ) )");
    bdd->build();
    std::cout << bdd->getExpression() << std::endl;
    std::cout << bdd->draw() << std::endl;
    std::cout << bdd->satcount() << std::endl;
    bdd->restr(2, false);
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
    //f->knight();
  //execQueens(8);
    if (argc == 2)
    {
		int value = atoi(argv[1]);
		if (value > 0)
			execQueens(value, "");
		else
			std::cerr << "Usage : ./queen nbcase [option]" << std::endl << "nbcase doit etre superieur a 0" << std::endl <<
			"option peut prendre la valeur allsat ou anysat ou satcount" << std::endl;
	}
	else if (argc == 3)
	{
	    int value = atoi(argv[1]);
	    std::string s = argv[2];
	    if (value > 0 && (s == "allsat" || s == "satcount" || s == "anysat"))
            execQueens(value, s);
		else
			std::cerr << "Usage : ./queen nbcase [option]" << std::endl << "nbcase doit etre superieur a 0" << std::endl <<
			"option peut prendre la valeur allsat ou anysat ou satcount" << std::endl;
	}
	else
        std::cerr << "Usage : ./queen nbcase [option]" << std::endl << "nbcase doit etre superieur a 0" << std::endl <<
			"option peut prendre la valeur allsat ou anysat ou satcount" << std::endl;

  /*GraphColoring *gc = new GraphColoring();
  gc->compute();*/

  return 0;
}
