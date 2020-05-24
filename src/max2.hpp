#ifndef _MAX2_HPP_
#define _MAX2_HPP_


template<class Real>
Real max2(Real a, Real b)
{
  if (a < b ) return b;
  return a;
}
#endif
