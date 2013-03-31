#include "include/Queens.h"
#include "include/GraphColoring.h"

using namespace std;

int main()
{
  //execQueens();
  
  GraphColoring *gc = new GraphColoring();
  gc->compute();
  
  return 0;
}
