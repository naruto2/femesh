#include <iostream>
#include <cstdio>
#include "xmesh.hpp"
#include "op.hpp"

using namespace std;

int main(int argc, char **argv)
{ 
  initop(argc,argv);
  vector<xyc> Z;
  vector<nde> N;

  scanxyc(Z);

  femesh(Z,N);

  if (defop("-x")) plotmesh(Z,N);
  else            printmesh(Z,N);
  return 0;
}
