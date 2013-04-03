#include <iostream>
#include <fstream>
#include "../../include/Queens.h"
#include "../../include/BDD.h"

using namespace std;

int main(int argc, char *argv[])
{
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
		
  return 0;
}
