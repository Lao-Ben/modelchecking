#include <iostream>
#include "include/Node.h"
#include "include/BDD.h"

using namespace std;

int main()
{
    int n  = 4;
    // créer un flux de sortie
    std::ostringstream oss;
    for (int i=0; i < n; i++)
    {
        if (i != 0)
        {
            oss << " & ";
        }
        oss << "( ";
        for (int j=0; j < n; j++)
        {
            if (j != 0)
            {
                oss << " | ";
            }
            oss << "( c"<<i<<j<<" & ( ";
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
            oss << " ) )";
        }
        oss << " )";
    }
    oss << " & ";
    for (int i=0; i < n; i++)
    {
        if (i != 0)
        {
            oss << " & ";
        }
        oss << "( ";
        for (int j=0; j < n; j++)
        {
            if (j != 0)
            {
                oss << " | ";
            }
            oss << "( c"<<j<<i<<" & ( ";
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
            oss << " ) )";
        }
        oss << " )";
    }
    oss << " & ";
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
        {
            oss << " & ";
        }
        oss << "( ";
        for (int j=0; j < n; j++)
        {
            if (j != 0)
            {
                oss << " | ";
            }
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
        }
        oss << " )";
    }
    oss << " & ";
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
        {
            oss << " & ";
        }
        oss << "( ";
        for (int j=0; j < n; j++)
        {
            if (j != 0)
            {
                oss << " | ";
            }
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
        }
        oss << " )";
    }
    // récupérer une chaîne de caractères
    std::string s = oss.str();
    Node* node = new Node();
    BDD* bdd = new BDD();
    bdd->setExpression("( "+s+" )");
    //bdd->setExpression("( a & ( b & c ) )");
    std::cout << "Expression : " << bdd->getExpression() << std::endl;
    bdd->setNbVar(n*n);

    cout << "Debut build"<<endl;
    node = bdd->build();
    cout << "Fin build"<<endl;
    cout << "Nombre de solution satisfaisante pour bdd: " << bdd->satcount() << endl;
    cout << "Une solution : " << bdd->anysat() << endl;
    cout << bdd->draw() << endl;
    return 0;
}
