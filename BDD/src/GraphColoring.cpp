//
//  GraphColoring.cpp
//  BDD2
//
//  Created by Benjamin Lefebvre on 29/03/13.
//  Copyright (c) 2013 Benjamin Lefebvre. All rights reserved.
//
//
// TODO :
//
//  - first optimization : color on 2 bools instead of 4 ((11 red 10 green 01 blue 00 yellow)
//  - second optimization : andfonc between the color definition condition and the color afectation condition
//

#include "../include/GraphColoring.h"

#include "../include/BDD.h"

#include <stdio.h>
#include <string.h>


const int NBVARS = 48 * 4;
const std::string RED 		= "R";
const std::string GREEN 	= "G";
const std::string BLUE 		= "B";
const std::string YELLOW 	= "Y";
std::vector<std::string> vertexArray;
BDD *bdd = NULL;


bool hasBegining (std::string const &fullString, std::string const &begining)
{
  if (fullString.length() >= begining.length()) {
    return (0 == fullString.compare (0, begining.length(), begining));
  } else {
    return false;
  }
}

bool hasEnding (std::string const &fullString, std::string const &ending)
{
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } else {
    return false;
  }
}


BDD* edge(std::string v1, std::string v2)
{
  BDD* bdd1;
  std::ostringstream constraint;

//  n'ajouter que si le sommet est rencontré pour la 1e fois
  if (std::find(vertexArray.begin(), vertexArray.end(), v1) == vertexArray.end()) {
  	constraint << "( " << RED << v1 <<  " xor " << GREEN << v1 <<  " xor " << BLUE << v1 <<  " xor " << YELLOW << v1 <<  " )";
  	constraint << " && ";
  }
  vertexArray.push_back(v1);

  if (std::find(vertexArray.begin(), vertexArray.end(), v2) == vertexArray.end()) {
	  constraint << "( " << RED << v2 <<  " xor " << GREEN << v2 <<  " xor " << BLUE << v2 <<  " xor " << YELLOW << v2 <<  " )";
  	constraint << " && ";
  }
  vertexArray.push_back(v2);
  
  constraint << "! ( ( "
  << RED << v1
  << " && " << RED << v2 << " ) || ( "
  << GREEN << v1 <<
  " && " << GREEN << v2 << " ) || ( "
  << BLUE << v1 <<
  " && " << BLUE << v2 << " ) || ( "
  << YELLOW << v1 <<
  " && " << YELLOW << v2 << " ) )";

  if (bdd == NULL)
  {
    bdd = new BDD();
    bdd->setNbVar(NBVARS);
    bdd->setExpression(constraint.str());
    bdd->build();
  }
  else
  {
    bdd1 = new BDD(bdd->getNbVar(), bdd->getVectVar(), bdd->getVectorNode(), bdd->getVectNode(), bdd->getNodeFalse(), bdd->getNodeTrue(), bdd->getVarorder(), bdd->getOrdervar(), bdd->getMaxIndice(), bdd->getOpmap());
//    bdd1 = bdd1->andfonc(bdd1, constraint.str());
//    bdd = bdd->andfonc(bdd, constraint.str());
    bdd1->setExpression(constraint.str());
    bdd1->build();
    bdd = bdd->andfonc(bdd,	bdd1);
    bdd = bdd->transferinfo(bdd1, bdd);
  }
  
  std::cout << "build sous bdd : " << v1 << "," << v2 << std::endl;
//  std::cout << "Nombre de solution satisfaisante pour sous bdd: " << bdd->satcount() << std::endl;
	return bdd;
}



void exportGraphColors (std::string solution)
{
  std::ofstream outFile("graph.data");
  
  std::istringstream iss(solution);
  std::string token;
  while(getline(iss, token, ';'))
  {
    if (hasEnding(token, "true"))
    {
      std::ostringstream oss;
      if (hasBegining(token, "[R"))
      {
        oss << token.substr(2,2) << " red";
      }
      else if (hasBegining(token, "[G"))
      {
        oss << token.substr(2,2) << " green";
      }
      else if (hasBegining(token, "[B"))
      {
        oss << token.substr(2,2) << " blue";
      }
      else if (hasBegining(token, "[Y"))
      {
        oss << token.substr(2,2) << " yellow";
      }
      std::cout << oss.str() << std::endl;
      outFile << oss.str() << std::endl;

    }
  }
  outFile.close();
}


int GraphColoring::compute()
{
  std::ostringstream constraint;

  // clocks for performance analysis
  clock_t start, end;
	double elapsed;
  start = clock();
  
  bdd = new BDD();
  bdd->setNbVar(NBVARS);
  
  
  edge("AL","FL"); edge("AL","GA"); edge("AL","MS"); edge("AL","TN"); // 5
  edge("AR","LA"); edge("AR","MO"); edge("AR","MS"); edge("AR","OK"); // 9
  edge("AR","TN"); edge("AR","TX"); edge("AZ","CA"); edge("AZ","NM"); // 13
  edge("AZ","NV"); edge("AZ","UT"); edge("CA","NV"); edge("CA","OR"); // 16
  edge("CO","KS"); edge("CO","NE"); edge("CO","NM"); edge("CO","OK"); // 19
  edge("CO","UT"); edge("CO","WY"); edge("CT","MA"); edge("CT","NY"); // 23
  edge("CT","RI"); edge("DE","MD"); edge("DE","NJ"); edge("DE","PA"); // 28
  edge("FL","GA"); edge("GA","NC"); edge("GA","SC"); edge("GA","TN"); // 31
  edge("IA","IL"); edge("IA","MN"); edge("IA","MO"); edge("IA","NE"); // 34
  edge("IA","SD"); edge("IA","WI"); edge("ID","MT"); edge("ID","NV"); // 37
  edge("ID","OR"); edge("ID","UT"); edge("ID","WA"); edge("ID","WY"); // 40
  edge("IL","IN"); edge("IL","KY"); edge("IL","MO"); edge("IL","WI"); // 40
  edge("IN","KY"); edge("IN","MI"); edge("IN","OH"); edge("KS","MO"); // 42
  edge("KS","NE"); edge("KS","OK"); edge("KY","MO"); edge("KY","OH"); // 44
  edge("KY","TN"); edge("KY","VA"); edge("KY","WV"); edge("LA","MS"); // 46
  edge("LA","TX"); edge("MA","NH"); edge("MA","NY"); edge("MA","RI"); // 48  // time 274 273
 // edge("MA","VT"); edge("MD","PA"); edge("MD","VA"); edge("MD","WV");
 // edge("ME","NH"); edge("MI","OH"); edge("MI","WI"); edge("MN","ND");
 // edge("MN","SD"); edge("MN","WI"); edge("MO","NE"); edge("MO","OK");
 // edge("MO","TN"); edge("MS","TN"); edge("MT","ND"); edge("MT","SD"); // time : 800s
 // edge("MT","WY"); edge("NC","SC"); edge("NC","TN"); edge("NC","VA");
 // edge("ND","SD"); edge("NE","SD"); edge("NE","WY"); edge("NH","VT");
 // edge("NJ","NY"); edge("NJ","PA"); edge("NM","OK"); edge("NM","TX");
 // edge("NV","OR"); edge("NV","UT"); edge("NY","PA"); edge("NY","VT");
 // edge("OH","PA"); edge("OH","WV"); edge("OK","TX"); edge("OR","WA");
 // edge("PA","WV"); edge("SD","WY"); edge("TN","VA"); edge("UT","WY");
 // edge("VA","WV");
  
  
  //std::cout << "Nombre de solution satisfaisante pour bdd: " << bdd->satcount() << std::endl;
  
  
  std::string solution = bdd->anysat();
  
  std::cout << "Une solution : " << solution << std::endl;
  
  // performance analysis
  end = clock();
  elapsed = ((double)end - start) / CLOCKS_PER_SEC;
  std::cout << "Execution time : " << elapsed << std::endl;
  
  exportGraphColors(solution);
  
  return 0;
}
