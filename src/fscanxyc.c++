#include <cstring>
#include "femesh.hpp"
using namespace std;


void printxyc( vector<xyc>& Z)
{
  for (unsigned int i=1; i<Z.size(); i++)
    printf("%d %f %f %s\n",i,Z[i].x,Z[i].y,Z[i].label?Z[i].label:"");
}


void fscanxyc(FILE *fp, vector<xyc>& Z)
{
  xyc z;
  double x=0.0, y=0.0;
  char label[99];
  char buf[1000];
  Z.push_back(z);

  while(1) {
    fgets(buf, 999, fp);
    if (feof(fp)) break;
    *label = 0;
    sscanf(buf,"%lf %lf %s",&x,&y,label);
    z.x = x; z.y = y;
    z.label = strdup(label);
    if (!strcmp(z.label,"")) z.label = 0;
    Z.push_back(z);
  }
}
