#ifndef NOTLAWSON_HPP_
#define NOTLAWSON_HPP_

#include <vector>
using namespace std;
#include "xmesh.hpp"
#include "fplane.hpp"

template<class Real>
int notLawson(vector<xyc>&Z,vector<nde>&N, Real x, Real y)
{
  int e,n;
  n = N.size();

  for(e=1;e<=n;e++){
    int a,b,c; Real x0,y0,x1,y1,x2,y2;
    a = N[e].a; b = N[e].b; c = N[e].c; 
    x0 = Z[a].x; x1 = Z[b].x; x2 = Z[c].x;
    y0 = Z[a].y; y1 = Z[b].y; y2 = Z[c].y;

    if     (fplane(x,y,0.0, x0,y0,1.0, x1,y1,0.0, x2,y2,0.0)>0.0) continue;
    else if(fplane(x,y,0.0, x0,y0,0.0, x1,y1,1.0, x2,y2,0.0)>0.0) continue;
    else if(fplane(x,y,0.0, x0,y0,0.0, x1,y1,0.0, x2,y2,1.0)>0.0) continue;
    else return e;
  }
  return  0;
}
#endif
