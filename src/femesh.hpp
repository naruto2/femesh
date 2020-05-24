#ifndef _FEMESH_HPP_
#define _FEMESH_HPP_

#include <vector>
#include <cstdio>

typedef struct{ int a, b, c, A, B, C; } nde;
typedef struct{ double x, y; char *label; } xyc;

extern void N_set( std::vector<nde>&,int ,int ,int ,int ,int ,int ,int );
extern int degeneracy( std::vector<xyc>&, std::vector<nde>&,int ,int );
extern void rotate_right( std::vector<nde>&,int);
extern void rotate_left( std::vector<nde>&,int);
extern void super_triangle(std::vector<xyc>&);
extern void LawsonSwap( std::vector<xyc>&, std::vector<nde>&);
extern void vanish_boundary_triangle( std::vector<xyc>&, std::vector<nde>&);
extern int count_nodes( std::vector<nde>&);
extern int generate_fN( std::vector<nde>&, std::vector<int>&);
extern void delaunay( std::vector<xyc>&, std::vector<nde>& );
extern void sortmesh( std::vector<xyc>&, std::vector<nde>& );
extern void p2( std::vector<xyc>&, std::vector<nde>& );
extern void fscanxyc( FILE *fp, std::vector<xyc>& );
extern void printxyc( std::vector<xyc>& );
extern void femesh( std::vector<xyc>&, std::vector<nde>& );
extern void plotmesh( std::vector<xyc>&, std::vector<nde>& );
extern void printmesh( std::vector<xyc>&, std::vector<nde>& );
extern int incircle( std::vector<xyc>&, std::vector<nde> &, int,int);
#endif
