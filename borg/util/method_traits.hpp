#ifndef METHOD_TRAITS_HPP
#define METHOD_TRAITS_HPP

#include <boost/config.hpp>

namespace borg {

//---------------------------------------------------------------------------  
template<typename Method> struct method_traits;

template<typename R, typename T>
  struct method_traits<R (T::*)()>
{
  BOOST_STATIC_CONSTANT(int, arity = 0);
  typedef R result_type;
  typedef T this_type;
};

template<typename R, typename T, typename A1>
  struct method_traits<R (T::*)(A1)>
{
  BOOST_STATIC_CONSTANT(int, arity = 1);
  typedef R result_type;
  typedef T this_type;
  typedef A1 arg1_type;
};

template<typename R, typename T, typename A1, typename A2>
  struct method_traits<R (T::*)(A1, A2)>
{
  BOOST_STATIC_CONSTANT(int, arity = 2);
  typedef R result_type;
  typedef T this_type;
  typedef A1 arg1_type;
  typedef A2 arg2_type;
};

template<typename R, typename T, typename A1, typename A2, typename A3>
  struct method_traits<R (T::*)(A1, A2, A3)>
{
  BOOST_STATIC_CONSTANT(int, arity = 3);
  typedef R result_type;
  typedef T this_type;
  typedef A1 arg1_type;
  typedef A2 arg2_type;
  typedef A3 arg3_type;
};

template<typename R, typename T, typename A1, typename A2, typename A3, typename A4>
  struct method_traits<R (T::*)(A1, A2, A3, A4)>
{
  BOOST_STATIC_CONSTANT(int, arity = 4);
  typedef R result_type;
  typedef T this_type;
  typedef A1 arg1_type;
  typedef A2 arg2_type;
  typedef A3 arg3_type;
  typedef A4 arg4_type;
};

template<typename R, typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
  struct method_traits<R (T::*)(A1, A2, A3, A4, A5)>
{
  BOOST_STATIC_CONSTANT(int, arity = 5);
  typedef R result_type;
  typedef T this_type;
  typedef A1 arg1_type;
  typedef A2 arg2_type;
  typedef A3 arg3_type;
  typedef A4 arg4_type;
  typedef A5 arg5_type;
};

template<typename mT>
  static inline int method_arity(mT m)
{
  typedef method_traits<mT> traits;
  return traits::arity;
};

} // namespace borg
//---------------------------------------------------------------------------  
#endif // METHOD_TRAITS_HPP
