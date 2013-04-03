#include <iostream>
#include <fstream>
#include "../../include/Queens.h"
#include "../../include/BDD.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
		std::cerr << "Usage : ./queen nbcase" << std::endl << "nbcase doit etre superieur a 0" << std::endl;
	else
	{
		int value = atoi(argv[1]);
		if (value > 0)
			execQueens(value);
		else
			std::cerr << "Usage : ./knight nbcase" << std::endl << "nbcase doit etre superieur a 0" << std::endl;
	}
		
  return 0;
}
