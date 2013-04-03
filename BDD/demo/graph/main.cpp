#include <iostream>
#include <fstream>
#include "../../include/GraphColoring.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 1)
		std::cerr << "Usage : ./graph" << std::endl;
	else
	{
		GraphColoring *gc = new GraphColoring();
		gc->compute();
	}
		
  return 0;
}
