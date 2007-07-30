#ifndef _cxx_operation_hpp_
#define _cxx_operation_hpp_

#include <math.h>
#include <typeinfo>
#include <boost/integer_traits.hpp>
#include <boost/detail/numeric_traits.hpp>

namespace operation {

//! Identity trait, returning the same type as the argument.
template<class valueT>
  struct identity_traits
  {
    typedef valueT value_type;
    typedef valueT result_type;
  };

//! Unary trait, (usually) returning a bigger type than the argument.
template<class valueT>
  struct unary_traits
  {
    typedef valueT value_type;
    typedef valueT result_type;
  };

template<>
  struct unary_traits<char>
  {
    typedef char value_type;
    typedef short result_type;
  };
  
template<>
  struct unary_traits<short>
  {
    typedef short value_type;
    typedef int result_type;
  };
  
template<>
  struct unary_traits<int>
  {
    typedef int value_type;
    typedef long long result_type;
  };
  
template<>
  struct unary_traits<float>
  {
    typedef float value_type;
    typedef double result_type;
  };

//! Binary traits for operations taking 2 parameters.
template<class aT, class bT>
  struct binary_traits
  {
    typedef aT a_type;
    typedef bT b_type;
    typedef aT result_type;
  };
  
//! Traits for difference ops (sub, add).s
template<class aT, class bT>
  struct difference_traits
  {
    typedef aT a_type;
    typedef bT b_type;
    typedef typename boost::detail::numeric_traits<aT>::difference_type result_type;    
  };
  
//! identify
template<class valueT, class traits = identity_traits<valueT> >
  class identity
{
public:
  typedef traits traits_type;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::result_type result_type;

  static inline result_type apply(value_type v)
  { return v; }
};

//! negation (0 - x)
template<class valueT, class traits = unary_traits<valueT> >
  class negate
{
public:
  typedef traits traits_type;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::result_type result_type;

  static inline result_type apply(value_type v)
  { return (0 - v); }
};

//! inversion
template<class valueT, class traits = unary_traits<valueT> >
  class inv
{
public:
  typedef traits traits_type;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::result_type result_type;

  static inline result_type apply(value_type v)
  { return (1.0 / v); }
};

//! Square root
template<class valueT, class traits = unary_traits<valueT> >
  class sqrt
{
public:
  typedef traits traits_type;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::result_type result_type;

  static inline result_type apply(value_type v)
  { return sqrt(v); }
};

//! 2nd power of operand
template<class valueT, class traits = unary_traits<valueT> >
  class pow2
{
public:
  typedef traits traits_type;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::result_type result_type;

  static inline result_type apply(value_type v) 
  { return v * v; }
};

template<class aT, class bT, class traits>
  class sub;

//! add
template<class aT, class bT, class traits = binary_traits<aT, bT> >
  class add
{
public:
  typedef traits traits_type;
  typedef typename traits_type::a_type a_type;
  typedef typename traits_type::b_type b_type;
  typedef typename traits_type::result_type result_type;
  typedef sub<aT, bT, binary_traits<aT, bT> > complement_type;

  static inline result_type apply(aT a, bT b) 
  { return a + b; }
  
  template<class _Tchar, class _Ctraits>
    static void print
    (const std::string &a, const std::string &b, std::basic_ostream<_Tchar, _Ctraits> &os = std::cout)
  { os << '('; os << a; os << '+'; os << b; os << ')'; }
};

//! sub
template<class aT, class bT, class traits = binary_traits<aT, bT> >
  class sub
{
public:
  typedef traits traits_type;
  typedef typename traits_type::a_type a_type;
  typedef typename traits_type::b_type b_type;
  typedef typename traits_type::result_type result_type;
  typedef add<aT, bT, binary_traits<aT, bT> > complement_type;

  static inline result_type apply(a_type a, b_type b)
  { return a - b; }
  
  template<class _Tchar, class _Ctraits>
    static void print
    (const std::string &a, const std::string &b, std::basic_ostream<_Tchar, _Ctraits> &os = std::cout)
  { os << '(' << a << '-' << b << ')'; }
};

template<class aT, class bT, class traits>
  class divide;

//! Mul
template<class aT, class bT, class traits = binary_traits<aT, bT> >
  class multiply
{
public:
  typedef traits traits_type;
  typedef typename traits_type::a_type a_type;
  typedef typename traits_type::b_type b_type;
  typedef typename traits_type::result_type result_type;
  typedef divide<aT, bT, binary_traits<aT, bT> > complement_type;

  static inline result_type apply(a_type a, b_type b)
  { return a * b; }
  
  template<class _Tchar, class _Ctraits>
    static void print
     (const std::string &a, const std::string &b, std::basic_ostream<_Tchar, _Ctraits> &os = std::cout)
  { os << '(' << a << '*' << b << ')'; }
};

//! div
template<class aT, class bT, class traits = binary_traits<aT, bT> >
  class divide
{
public:
  typedef traits traits_type;
  typedef typename traits_type::a_type a_type;
  typedef typename traits_type::b_type b_type;
  typedef typename traits_type::result_type result_type;
  typedef multiply<aT, bT, binary_traits<aT, bT> > complement_type;

  static inline result_type apply(a_type a, b_type b)
  { return a / b; }
  
  template<class _Tchar, class _Ctraits>
    static void print
     (const std::string &a, const std::string &b, std::basic_ostream<_Tchar, _Ctraits> &os = std::cout)
  { os << '('; os << a; os << '/'; os << b; os << ')'; }
};

} // end of namespace operation
  
#endif // _cxx_operation_hpp_
