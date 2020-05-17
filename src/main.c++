#include <iostream>
#include <cstdio>
#include "xmesh.hpp"
#include "op.hpp"

using namespace std;

int main(int argc, char **argv)
{ 
  initop(argc,argv);
  vector<xyc> Z;
  vector<nde> N;
  ifstream ifs;

  if (!defop("-f") && argc > 1 ) {
    ifs.open(argv[1]);
    if (!ifs) {
	cerr << "Error: Can't open file (femesh)" << endl;
	return 0;
    }
    in2xyc(ifs,Z);
    ifs.close();
    goto ToDo;
  }
  
  if (!defop("-f")){
    fprintf(stderr,"Usage: femesh -f (filename.xyc)\n");
    fprintf(stderr,"       femesh -f (filename.xyc) -o (output.mesh)\n");
    return 0;
  }
  
  if ( defop("-f") ) {
    if (getop("-f") == "-" ) {
      in2xyc(cin,Z);
    }
    else {
      ifs.open(getop("-f"));
      if (!ifs) {
	cerr << "Error: Can't open file (femesh)" << endl;
	return 0;
      }
      in2xyc(ifs,Z); 
      ifs.close();
    }
  } else {
    in2xyc(cin,Z);
  }

 ToDo:
  delaunay(Z, N);
  sortmesh(Z, N);
  p2(Z, N);

  if (!defop("-o") && !defop("-x")) {
    outmesh(cout,Z,N);
    return 0;
  }
  
  if ( defop("-o") ) {
    if ( getop("-o") == "-" ) {
      outmesh(cout,Z,N);
    }
    else {
      ofstream ofs;
      ofs.open(getop("-o").c_str(), ios::out);
      outmesh(ofs,Z,N);
    }
  }
  else
    plotmesh(Z,N);

  return 0;
}
