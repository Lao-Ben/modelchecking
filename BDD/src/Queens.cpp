//
//  Queens.cpp
//  BDD2
//
//  Created by Benjamin Lefebvre on 26/03/13.
//  Copyright 2013 Benjamin Lefebvre. All rights reserved.
//

#include "../include/Queens.h"


int execQueens(int n, std::string com)
{
  // clocks for performance analysis
  clock_t start, end;
	double elapsed;
  start = clock();

  std::ostringstream namefich;
  BDD* bdd = new BDD();
  bdd->setNbVar(n*n);
  int pos = 0;
  std::ostringstream oss;
  namefich << "test" << pos << ".txt";
  std::string namefichstr = namefich.str();
  std::ofstream fichier(namefichstr, std::ios::out | std::ios::trunc);
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
  std::cout << "fin troisieme bdd" << std::endl;
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
  std::cout << "fin quatrieme bdd" << std::endl;
  bdd = bdd->andfonc(bdd, bdd1);
  std::cout << "fin apply1" << std::endl;
  bdd = bdd->andfonc(bdd, bdd2);
  std::cout << "fin apply2" << std::endl;
  bdd = bdd->andfonc(bdd, bdd3);
  std::cout << "fin apply3" << std::endl;
  bdd = bdd->andfonc(bdd, bdd4);
  std::cout << "fin apply4" << std::endl;
  if (com == "satcount")
    std::cout << "Nombre de solution satisfaisante pour bdd: " << bdd->satcount() << std::endl;
  else if (com == "anysat")
    std::cout << "Une solution: " << bdd->anysat() << std::endl;
  else if (com == "allsat")
  {
	std::cout << "Toutes les solutions:" << std::endl;
    bdd->allsat();
  }



  // performance analysis
  end = clock();
  elapsed = ((double)end - start) / CLOCKS_PER_SEC;
  std::cout << "Execution time : " << elapsed << std::endl;

  return 0;
}
