#ifndef _FEMESH_HPP_
#define _FEMESH_HPP_

typedef struct{ int a, b, c, A, B, C; } nde;
typedef struct{ double x, y; char *label; } xyc;

extern void femesh( std::vector<xyc>&, std::vector<nde>& );
extern void printxyc( std::vector<xyc>& );
extern void fscanxyc( FILE *fp, std::vector<xyc>& );
extern void plotmesh( std::vector<xyc>&, std::vector<nde>& );
extern void printmesh( std::vector<xyc>&, std::vector<nde>& );
#endif
