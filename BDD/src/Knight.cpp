//
//  Knight.cpp
//  BDD2
//
//  Created by Thibault Lapassade on 03/04/13.
//  Copyright 2013 Thibault Lapassade. All rights reserved.
//

#include "../include/Knight.h"

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

int execKnight(int n)
{
  // clocks for performance analysis
  clock_t start, end;
	double elapsed;
  start = clock();

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



  // performance analysis
  end = clock();
  elapsed = ((double)end - start) / CLOCKS_PER_SEC;
  std::cout << "Execution time : " << elapsed << std::endl;

  return 0;
}
