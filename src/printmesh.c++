#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include "op.hpp"
#include "xmesh.hpp"

using namespace std;


static char *label(vector<xyc>&Z,int i)
{ static char *normal = (char*)"";
  return Z[i].label==NULL? normal:Z[i].label;
}


void printmesh(vector<xyc>&Z,vector<nde>&N)
{

  if ( defop("-o") && strcmp(op("-o").c_str(),"-") )
    freopen( op("-o").c_str(), "w", stdout);

  printf("<xyc>\n");

  for (unsigned int i=1; i<Z.size(); i++) { 
    printf("%4d %.9f %.9f %s\n",i,Z[i].x,Z[i].y,label(Z,i));
  }

  printf("<nde>\n");

  for (unsigned int i=1; i<N.size(); i++) {
    printf("%4d  %4d %4d %4d  %4d %4d %4d\n",
            i, N[i].a,N[i].b,N[i].c,N[i].A,N[i].B,N[i].C);
  }
}
