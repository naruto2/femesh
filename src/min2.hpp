#ifndef _MIN2_HPP_
#define _MIN2_HPP_


template<class Real>
Real min2(Real a, Real b)
{
  if ( a < b ) return a;
  return b;
}
#endif
