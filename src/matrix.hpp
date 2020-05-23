#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <map>

using namespace std;

template<typename T>
class matrix : public vector< map<long, T> > {

public:
  matrix(){}
  matrix(long n) : vector< map<long, T> >(n){};
};


int solver(matrix<double>&A, vector<double>&x, vector<double>&b);
#endif
