#include <cstdio>
#include <cstdlib>
#include <vector>
#include "op.hpp"
#include "femesh.hpp"
using namespace std;


void plotmesh(vector<xyc>&Z, vector<nde>&N)
{
  FILE *fp;
  unsigned long e, a, b, c;

  fp = popen("export QT_LOGGING_RULES='*=false'; gnuplot","w");

  if ( defop("-n") ) {
    for(unsigned long v=1;v<Z.size();v++)
      fprintf(fp,"set label \"%ld\" at %f, %f;\n",v,Z[v].x,Z[v].y);
  }

  fprintf(fp,"plot '-' title \"\" with lines\n");

  for (e=1; e<N.size(); e++) {
    a = N[e].a, b = N[e].b, c = N[e].c;
    fprintf(fp,"%f %f\n",Z[a].x,Z[a].y);
    fprintf(fp,"%f %f\n",Z[b].x,Z[b].y);
    fprintf(fp,"%f %f\n",Z[c].x,Z[c].y);
    fprintf(fp,"%f %f\n",Z[a].x,Z[a].y);
    fprintf(fp,"\n\n");
  }
  
  fprintf(fp,"e\n");
  fflush(fp);
  getchar();
  fprintf(fp,"exit\n");
  pclose(fp);
}
