#include <vector>
#include "femesh.hpp"
using namespace std;


void N_set(vector<nde>&N,int n,int i,int j,int k,int I,int J,int K)
{
  N[n].a=i;N[n].b=j;N[n].c=k;N[n].A=I;N[n].B=J;N[n].C=K;
}
