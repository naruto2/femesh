#include "xmesh.hpp"


extern void delaunay( vector<xyc>&, vector<nde>& );
extern void sortmesh( vector<xyc>&, vector<nde>& );
extern void p2( vector<xyc>&, vector<nde>& );


void femesh(vector<xyc>&Z, vector<nde>&N)
{
  delaunay(Z,N);
  sortmesh(Z,N);
  p2(Z,N);
}
