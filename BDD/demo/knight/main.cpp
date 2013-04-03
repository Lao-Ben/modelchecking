#include <iostream>
#include <fstream>
#include "../../include/Knight.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
		std::err << "Usage : ./knight nbcase" << std::endl << "nbcase doit etre superieur a 0" << std::endl;
	else
	{
		int value = atoi(argv[1]);
		if (value > 0)
			execKnight(4);
		else
			std::err << "Usage : ./knight nbcase" << std::endl << "nbcase doit etre superieur a 0" << std::endl;
	}
		
  return 0;
}
