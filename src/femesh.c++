#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>
#include <functional>
#include "femesh.hpp"
#include "matrix.hpp"
using namespace std;


template<class Real>
Real distance2(Real x0,Real y0,Real x1,Real y1)
{
  return ((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
}


template<class Real>
static Real fplane(Real x, Real y, Real z,
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
static int notLawsonSearch(std::vector<xyc>&Z,std::vector<nde>&N,
			   Real x, Real y)
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


template<class Real>
static int LawsonSearch(std::vector<xyc>&Z, std::vector<nde>&N,
			int e, Real x, Real y)
{
  int n, count = 0;
  int a,b,c; Real x0,y0,x1,y1,x2,y2;
  n = N.size()-1;
  while(1){
    a = N[e].a; b = N[e].b; c = N[e].c;
    x0 = Z[a].x; x1 = Z[b].x; x2 = Z[c].x;
    y0 = Z[a].y; y1 = Z[b].y; y2 = Z[c].y;
    if(n<count++) return notLawsonSearch(Z,N,x,y);

    if     (fplane(x,y,0.0, x0,y0,1.0, x1,y1,0.0, x2,y2,0.0)>0.0) e = N[e].A;
    else if(fplane(x,y,0.0, x0,y0,0.0, x1,y1,1.0, x2,y2,0.0)>0.0) e = N[e].B;
    else if(fplane(x,y,0.0, x0,y0,0.0, x1,y1,0.0, x2,y2,1.0)>0.0) e = N[e].C;
    else return e;
  }
}


static void rotate_left(vector<nde>&N,int i)
{ int a,b,c,A,B,C;
  a=N[i].a; b=N[i].b; c=N[i].c; A=N[i].A; B=N[i].B; C=N[i].C;
  N[i].a=b; N[i].b=c; N[i].c=a; N[i].A=B; N[i].B=C; N[i].C=A;
}


static void rotate_right(vector<nde>&N,int i)
{ int a,b,c,A,B,C;
  a=N[i].a; b=N[i].b; c=N[i].c; A=N[i].A; B=N[i].B; C=N[i].C;
  N[i].a=c; N[i].b=a; N[i].c=b; N[i].A=C; N[i].B=A; N[i].C=B;
}


static int degeneracy(vector<xyc>&Z, vector<nde>&N,int e1,int e2)
{ int a, d, W, Y; double x1,y1,x2,y2,x3,y3,x4,y4;

  if(N[e1].B == e2) { rotate_left(N,e1); } if(N[e1].C == e2) { rotate_right(N,e1); }
  if(N[e2].B == e1) { rotate_left(N,e2); } if(N[e2].C == e1) { rotate_right(N,e2); }

  x1= Z[N[e1].a].x;  y1= Z[N[e1].a].y;
  x2= Z[N[e2].a].x;  y2= Z[N[e2].a].y;
  x3= Z[N[e2].b].x;  y3= Z[N[e2].b].y;
  x4= Z[N[e2].c].x;  y4= Z[N[e2].c].y;
 
  if(distance2(x1,y1,x2,y2)==distance2(x3,y3,x4,y4)) return 1;
  
  a=N[e1].a; Y=N[e1].C;
  d=N[e2].a; W=N[e2].C;
  N[e1].b=d; N[e1].A=W; N[e1].C=e2;
  N[e2].b=a; N[e2].A=Y; N[e2].C=e1;

  if(N[W].B == e2) { rotate_left(N,W); } if(N[W].C == e2) { rotate_right(N,W); }
  if(N[Y].B == e1) { rotate_left(N,Y); } if(N[Y].C == e1) { rotate_right(N,Y); }
  N[W].A = e1; N[Y].A = e2;

  return 0;
}


static void N_set(vector<nde>&N,int n,int i,int j,int k,int I,int J,int K)
{
  N[n].a=i;N[n].b=j;N[n].c=k;N[n].A=I;N[n].B=J;N[n].C=K;
}


static int incircle(vector<xyc>&Z, vector<nde> &N, int p,int e2)
{
  static double x,y,x0,y0,x1,y1,x2,y2;
  
  if ( e2 == 0 ) return 0;
  
  x=Z[p].x; y=Z[p].y;
  x0=Z[N[e2].a].x;  y0=Z[N[e2].a].y;
  x1=Z[N[e2].b].x;  y1=Z[N[e2].b].y;
  x2=Z[N[e2].c].x;  y2=Z[N[e2].c].y;

  static matrix<double> A(3);
  static vector<double> U(3),B(3);

  A[0][0] = x0; A[0][1] = y0; A[0][2] = 1.0;
  A[1][0] = x1; A[1][1] = y1; A[1][2] = 1.0;
  A[2][0] = x2; A[2][1] = y2; A[2][2] = 1.0;
  
  B[0] = x0*x0 + y0*y0;
  B[1] = x1*x1 + y1*y1;
  B[2] = x2*x2 + y2*y2;
  
  solver(A,U,B);
  
  return distance2(x0,y0,U[0]/2.0,U[1]/2.0) - distance2(x,y,U[0]/2.0,U[1]/2.0)
    > 0.0 ? 1:0;
}


static void LawsonSwap(vector<xyc>&Z, vector<nde>&N)
{
  int z, i,n;

  z=Z.size()-4;

  N_set(N,1,z+1,z+2,z+3,0,0,0);

  n=1;
  for (i=1;i<=z; i++) {

    int e0,e1,e2,a,b,c,A,B,C; 

    e0=LawsonSearch(Z,N,n,Z[i].x,Z[i].y); e1=n+1; e2=n+2; n+=2;

    a=N[e0].a,b=N[e0].b,c=N[e0].c,A=N[e0].A,B=N[e0].B,C=N[e0].C;

    N_set(N, 0,0,0,0, 0, 0, 0);
    N_set(N,e0,i,b,c,A ,e1,e2);  
    N_set(N,e1,a,i,c,e0,B, e2);
    N_set(N,e2,a,b,i,e0,e1, C);
    
    if(N[B].A==e0) N[B].A=e1;
    if(N[B].B==e0) N[B].B=e1;
    if(N[B].C==e0) N[B].C=e1;

    if(N[C].A==e0) N[C].A=e2;
    if(N[C].B==e0) N[C].B=e2;
    if(N[C].C==e0) N[C].C=e2;
    
    stack<int> s;
    s.push(e0); s.push(e1); s.push(e2);
    
    while(s.size()!=0){
      e1 = s.top();
      s.pop();

      if(incircle(Z,N,i,(e2= (N[e1].a==i?N[e1].A:
			     (N[e1].b==i?N[e1].B:
			      N[e1].C))))){
	if(!degeneracy(Z,N,e1,e2)){ s.push(e1); s.push(e2);}
      }
    }
  }
}


static int count_nodes(vector<nde>&N)
{
  int n=0, i;
  for (i=1; i<(int)N.size(); i++)
    if (N[i].a!=0) n++;
  return n;
}


static int generate_fN(vector<nde>&N,vector<int>&fN)
{
  int i, n=0;
  for (i=1; i<(int)fN.size(); i++) {
    while(N[n].a==0) n++;
    fN[i] = n++;
  }
  return n;
}


template<class Real>
static Real max2(Real a, Real b)
{
  if (a < b ) return b;
  return a;
}


template<class Real>
static Real min2(Real a, Real b)
{
  if ( a < b ) return a;
  return b;
}


static void super_triangle(vector<xyc>&Z)
{
  double xmin,ymin,xmax,ymax,length;
  int z, i;
  static char super_node[] = "super_node";
  z=Z.size(); z -=4;
  xmin = Z[1].x; ymin = Z[1].y;
  xmax = Z[1].x; ymax = Z[1].y;
  for (i=2; i<=z; i++){
    xmin=min2(xmin,Z[i].x); xmax=max2(xmax,Z[i].x);
    ymin=min2(ymin,Z[i].y); ymax=max2(ymax,Z[i].y);
  }
  length = max2(xmax-xmin, ymax-ymin);
  Z[z+1].x = xmin - length/2.0;
  Z[z+1].y = ymin - length/2.0;
  Z[z+2].x = xmin + length*3.0;
  Z[z+2].y = ymin - length/2.0;
  Z[z+3].x = xmin - length/2.0;
  Z[z+3].y = ymin + length*3.0;
  Z[z+1].label = super_node;
  Z[z+2].label = super_node;
  Z[z+3].label = super_node;
}   


static void vanish_boundary_triangle(vector<xyc>&Z, vector<nde>&N)
{

  int A,B,C,i;

  for (i=1; i<(int)N.size(); i++) {
    if(Z[N[i].a].label==NULL||Z[N[i].b].label==NULL||Z[N[i].c].label==NULL)
      continue;

    
    A = N[i].A;
    B = N[i].b;
    C = N[i].c;
    if(N[A].A == i) N[A].A=0;
    if(N[A].B == i) N[A].B=0;
    if(N[A].C == i) N[A].C=0;
    if(N[B].A == i) N[B].A=0;
    if(N[B].B == i) N[B].B=0;
    if(N[B].C == i) N[B].C=0;
    if(N[C].A == i) N[C].A=0;
    if(N[C].B == i) N[C].B=0;
    if(N[C].C == i) N[C].C=0;

    N[i].a=0;
    N[i].b=0;
    N[i].c=0;
    N[i].A=0;
    N[i].B=0;
    N[i].C=0;
  }
}


static void delaunay(vector<xyc>&Zo, vector<nde>&No)
{ int i, n, z; 
  vector<xyc> Z;
  vector<nde> N, N0;
  vector<int> fN, fNinv, fZ,fZinv;
  Zo.resize(Zo.size()+3);
  
  z = Zo.size()-1;
  Z.resize(z+1);
  for ( i=0; i<z; i++) Z[i] = Zo[i];
  
  super_triangle(Z);
  N.resize(Z.size()*3);
  LawsonSwap(Z,N);
  vanish_boundary_triangle(Z, N);
  
  fN.resize(count_nodes(N)+1);
  n = generate_fN(N,fN);
  
  N0.resize(fN.size());
  for (i=1;i<(int)N0.size(); i++) N0[i]=N[fN[i]];
  
  fNinv.resize(n);
  fZ.resize(z+1);

  for (i=1; i<(int)fN.size(); i++) fNinv[fN[i]]=i;

  for (i=1; i<=(int)N0.size(); i++) {
    N0[i].A = fNinv[N0[i].A];
    N0[i].B = fNinv[N0[i].B];
    N0[i].C = fNinv[N0[i].C];
  }  

  for(z=0, i=1; i<(int)N0.size(); i++) {
    if (fZ[N0[i].a] == 0) fZ[N0[i].a] = ++z;
    if (fZ[N0[i].b] == 0) fZ[N0[i].b] = ++z;
    if (fZ[N0[i].c] == 0) fZ[N0[i].c] = ++z;
  }
    
  for(i=1; i<(int)N0.size(); i++) {
    N0[i].a = fZ[N0[i].a];
    N0[i].b = fZ[N0[i].b];
    N0[i].c = fZ[N0[i].c];
  }  

  fZinv.resize(z+1);
  for (i=1; i<(int)fZ.size(); i++) fZinv[fZ[i]] = i;

  Zo.resize(z+1);
  for (i=1; i<=z; i++) Zo[i]  = Z[fZinv[i]];  

  No.resize(N0.size());
  for (i=0;i<(int)N0.size();i++) No[i] = N0[i];

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


#define for_ABC(i,abcABC) \
  if(int jABC=0 == 0)for(IntIterator i((int *)&abcABC);jABC++<7; ++i)if(4<jABC)

#define for_ABC2(i,abcABC) \
  if(int jABC2=0 == 0)for(IntIterator i((int *)&abcABC);jABC2++<7; ++i)if(4<jABC2)


static void p2( vector<xyc>&Z, vector<nde>&N)
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
}


typedef struct { int i, a, b, c, A, B, C; double x, y; } ende;
typedef struct { int i; double x, y; char *label; } exyc;

bool operator<(const exyc& left, const exyc& right)
{
  if ( left.y == right.y ) return left.x < right.x;
  return left.y < right.y;
}

bool operator>(const exyc& left, const exyc& right)
{
  if ( left.y == right.y ) return left.x > right.x;
  return left.y > right.y;
}


bool operator<(const ende& left, const ende& right)
{
  if ( left.y == right.y ) return left.x < right.x;
  return left.y < right.y;
}

bool operator>(const ende& left, const ende& right)
{
  if ( left.y == right.y ) return left.x > right.x;
  return left.y > right.y;
}


static void sortmesh(vector<xyc> &Z0, vector<nde> &N0)
{
  unsigned long i;

  vector<exyc> Z(Z0.size());
  vector<ende> N(N0.size());
  
  // 重心を求めるフェーズ
  for ( i=0; i<Z.size(); i++) {
    Z[i].i = i;
    Z[i].x = Z0[i].x;
    Z[i].y = Z0[i].y;
    Z[i].label = Z0[i].label;
  }
  for ( i=0; i<N.size(); i++) {
    N[i].i = i;
    N[i].a = N0[i].a;
    N[i].b = N0[i].b;
    N[i].c = N0[i].c;
    N[i].A = N0[i].A;
    N[i].B = N0[i].B;
    N[i].C = N0[i].C;
    N[i].x = (Z[N0[i].a].x + Z[N0[i].b].x + Z[N0[i].c].x ) / 3.0;
    N[i].y = (Z[N0[i].a].y + Z[N0[i].b].y + Z[N0[i].c].y ) / 3.0;
  }

  // ソートするフェーズ
  sort(&Z[1],&Z[Z.size()]);
  sort(&N[1],&N[N.size()]);


  // 逆関数を構成するフェーズ
  vector<int> f(Z.size());
  for ( i = 0; i<Z.size(); i++) { f[Z[i].i] =i; }

  vector<int> g(N.size());
  for ( i = 0; i<N.size(); i++) { g[N[i].i] =i; }
  

  // 要素-節点対応表を変換するフェーズ
  for ( i = 0; i<N.size(); i++ )
    {
      N[i].a = f[N[i].a];
      N[i].b = f[N[i].b];
      N[i].c = f[N[i].c];
    }
  for ( i = 0; i<N.size(); i++ )
    {
      N[i].A = g[N[i].A];
      N[i].B = g[N[i].B];
      N[i].C = g[N[i].C];
    }
  
  // 書き戻すフェーズ
  for ( i=0; i<Z.size(); i++) {
    Z0[i].x = Z[i].x;
    Z0[i].y = Z[i].y;
    Z0[i].label = Z[i].label;
  }
  for ( i=0; i<N.size(); i++) {
    N0[i].a = N[i].a;
    N0[i].b = N[i].b;
    N0[i].c = N[i].c;
    N0[i].A = N[i].A;
    N0[i].B = N[i].B;
    N0[i].C = N[i].C;
  }
}


void femesh(vector<xyc>&Z, vector<nde>&N)
{
  delaunay(Z,N);
  sortmesh(Z,N);
  p2(Z,N);
}
