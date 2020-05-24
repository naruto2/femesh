#ifndef _FEMESH_HPP_
#define _FEMESH_HPP_
#include <cstdio>
#include <vector>
#include <iterator>


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


template<class Real>
Real fplane(Real x, Real y, Real z,
	    Real x0,Real y0,Real z0,
	    Real x1,Real y1,Real z1,
	    Real x2,Real y2,Real z2)
{ static Real xn,yn,zn;

  xn = (y1-y0)*(z2-z0)-(z1-z0)*(y2-y0);
  yn = (z1-z0)*(x2-x0)-(x1-x0)*(z2-z0);
  zn = (x1-x0)*(y2-y0)-(y1-y0)*(x2-x0);

  return xn*x+yn*y+zn*z-(xn*x0+yn*y0+zn*z0);
}


template<class Real>
Real distance2(Real x0,Real y0,Real x1,Real y1)
{
  return ((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
}


static const int intNULL = 2111111111;

class IntIterator : public std::iterator<std::bidirectional_iterator_tag, int, void>
{
public:
  IntIterator(int* begin)
    : m_pos(begin)
  {};

  IntIterator(int* begin, int)
    : m_pos(begin)
  {};

  IntIterator()
    : m_pos(NULL)
  {};

  int& operator *() const {
    return *m_pos;
  };

  IntIterator& operator ++(){
    ++m_pos;
    return *this;
  };

  IntIterator operator ++(int){
    int* p = m_pos;
    ++(*this);
    return IntIterator(p);
  };

  IntIterator& operator --(){
    --m_pos;
    return *this;
  };

  const bool operator !=(const IntIterator& ite) const {
    if(ite.m_pos == NULL && *m_pos == intNULL) return false;
    return (m_pos != ite.m_pos);
  };

  const bool operator ==(const IntIterator& ite) const {
    if(ite.m_pos == NULL && *m_pos == intNULL) return true;
    return (m_pos == ite.m_pos);
  };

private:
  int* m_pos;
};
  

#define for_nde(i,abcABC) \
if(int jabcABC=0 == 0)for(IntIterator i((int *)&abcABC);jabcABC++<7; ++i)

#define for_nde2(i,abcABC) \
if(int jabcABC2=0 == 0)for(IntIterator i((int *)&abcABC);jabcABC2++<7; ++i)

#define for_abc(i,abcABC) \
if(int jabc=0 == 0)for(IntIterator i((int *)&abcABC);jabc++<4; ++i)

#define for_ABC(i,abcABC) \
if(int jABC=0 == 0)for(IntIterator i((int *)&abcABC);jABC++<7; ++i)if(4<jABC)

#define for_ABC2(i,abcABC) \
if(int jABC2=0 == 0)for(IntIterator i((int *)&abcABC);jABC2++<7; ++i)if(4<jABC2)


template<class Real>
Real max2(Real a, Real b)
{
  if (a < b ) return b;
  return a;
}


template<class Real>
Real min2(Real a, Real b)
{
  if ( a < b ) return a;
  return b;
}


template<class Real>
int Lawson(std::vector<xyc>&Z, std::vector<nde>&N,int e, Real x, Real y)
{ 
  int n, count = 0;
  int a,b,c; Real x0,y0,x1,y1,x2,y2;
  n = N.size()-1;
  while(1){
    a = N[e].a; b = N[e].b; c = N[e].c; 
    x0 = Z[a].x; x1 = Z[b].x; x2 = Z[c].x;
    y0 = Z[a].y; y1 = Z[b].y; y2 = Z[c].y;
    if(n<count++) return notLawson(Z,N,x,y);
    
    if     (fplane(x,y,0.0, x0,y0,1.0, x1,y1,0.0, x2,y2,0.0)>0.0) e = N[e].A;
    else if(fplane(x,y,0.0, x0,y0,0.0, x1,y1,1.0, x2,y2,0.0)>0.0) e = N[e].B;
    else if(fplane(x,y,0.0, x0,y0,0.0, x1,y1,0.0, x2,y2,1.0)>0.0) e = N[e].C;
    else return e;
  }
}


template<class Real>
int notLawson(std::vector<xyc>&Z,std::vector<nde>&N, Real x, Real y)
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
