#include "femesh.hpp"
#include "matrix.hpp"
#include "distance2.hpp"
using namespace std;


int incircle(vector<xyc>&Z, vector<nde> &N, int p,int e2)
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
