#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <map>


template<typename T>
class matrix : public std::vector< std::map<long, T> > {

public:
  matrix(){}
  matrix(long n) : std::vector< std::map<long, T> >(n){};
};


int solver(matrix<double>&A,std::vector<double>&x,std::vector<double>&b);
#endif
