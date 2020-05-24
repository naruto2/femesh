#include <vector>
#include "femesh.hpp"
using namespace std;


int generate_fN(vector<nde>&N,vector<int>&fN)
{
  int i, n=0;
  for (i=1; i<(int)fN.size(); i++) {
    while(N[n].a==0) n++;
    fN[i] = n++;
  }
  return n;
}
