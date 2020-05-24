#include <cstdio>
#include <vector>
#include "femesh.hpp"
#include "for_nde.hpp"
using namespace std;


void p2( vector<xyc>&Z, vector<nde>&N)
{
  int i, e;

  e = N.size();

  for (i=1; i<e; i++) for_ABC (m,N[i]) *m = -(*m);

  unsigned int n = Z.size();

  for (i=1; i<e; i++) {
    for_ABC (m,N[i])
      if ( *m<=0 ) {
	for_ABC2 (u,N[-(*m)]) if ( *u == -i ) *u = n;
	*m = n++;
      }
  }

  return;
  for(i=1;i<(int)N.size();i++) printf("%d %d %d %d %d %d %d\n",i,
				      N[i].a,N[i].b,N[i].c,
				      N[i].A,N[i].B,N[i].C);
}
