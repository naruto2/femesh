#include <cstdio>
#include <vector>
#include "op.hpp"
#include "femesh.hpp"
using namespace std;


int main(int argc, char **argv)
{ 
  FILE *fp = stdin;
  vector<xyc> Z;
  vector<nde> N;

  initop(argc,argv);
  
  if (argc > 1 ) fp = fopen(argv[1],"r");

  fscanxyc(fp,Z);

  femesh(Z,N);

  if (defop("-x")) plotmesh(Z,N);
  else            printmesh(Z,N);
  return 0;
}
