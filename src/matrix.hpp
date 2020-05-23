#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <unistd.h>

using namespace std;

template<typename T>
class matrix : public vector< map<long, T> > {

public:
  matrix(){}
  matrix(long n) : vector< map<long, T> >(n){};
};

#endif
