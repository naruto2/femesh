#ifndef _FEMESH_HPP_
#define _FEMESH_HPP_

#include <vector>
#include <cstdio>

using namespace std;

typedef struct{ int a, b, c, A, B, C; } nde;
typedef struct{ double x, y; char *label; } xyc;

extern void fscanxyc( FILE *fp, vector<xyc>& );
extern void printxyc( vector<xyc>& );
extern void femesh( vector<xyc>&, vector<nde>& );
extern void plotmesh( vector<xyc>&, vector<nde>& );
extern void printmesh( vector<xyc>&, vector<nde>& );
#endif
