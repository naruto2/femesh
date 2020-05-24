#include "femesh.hpp"
using namespace std;

void femesh(vector<xyc>&Z, vector<nde>&N)
{
  delaunay(Z,N);
  sortmesh(Z,N);
  p2(Z,N);
}
