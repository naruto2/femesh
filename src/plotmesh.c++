#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "xmesh.hpp"

#define  dim1(N) (long)(N.size()-1)

using namespace std;


void plotmesh(vector<xyc>&Z,vector<nde>&N)
{
  FILE *fp = stdout;
  unsigned long e, a, b, c;

  fp = popen("gnuplot","w");


  fprintf(fp,"plot '-' title \"\" with lines\n");
  
  for(e=1;e<N.size();e++){
    a = N[e].a, b = N[e].b, c = N[e].c;
    fprintf(fp,"%f %f\n",Z[a].x,Z[a].y);
    fprintf(fp,"%f %f\n",Z[b].x,Z[b].y);
    fprintf(fp,"%f %f\n",Z[c].x,Z[c].y);
    fprintf(fp,"%f %f\n",Z[a].x,Z[a].y);
    fprintf(fp,"\n\n");
  }

  fprintf(fp,"e\n");
  fflush(fp);
  sleep(65535);
  pclose(fp);
  exit(0);
}
