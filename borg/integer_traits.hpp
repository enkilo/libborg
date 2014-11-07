#ifndef BORG_INTEGER_TRAITS_HPP
#define BORG_INTEGER_TRAITS_HPP

#include <string>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/integer/static_log2.hpp>

namespace borg {

//---------------------------------------------------------------------------
template<class T>
struct integer_traits : boost::integer_traits<T>
{
  typedef T type;
  typedef boost::integer_traits<T> base_type;
  
  //static const unsigned int const_range = (base_type::const_max - base_type::const_min + 1);
  enum { const_range = (base_type::const_max - base_type::const_min + 1) };
  static const unsigned int const_bits = boost::static_log2<const_range>::value;
  //enum { const_bits = boost::static_log2<const_range>::value };
};

//---------------------------------------------------------------------------
template<>
struct integer_traits<int> : boost::integer_traits<int>
{
  typedef int type;
  
  static const unsigned long long const_range = 1LL + const_max - const_min;
  static const unsigned int const_bits = 32;
};

//---------------------------------------------------------------------------
template<>
struct integer_traits<unsigned int> : boost::integer_traits<unsigned int>
{
  typedef unsigned int type;
  
  static const unsigned long long const_range = const_max + 1;
  static const unsigned int const_bits = 32;
};

//---------------------------------------------------------------------------
template<>
struct integer_traits<long> : boost::integer_traits<long>
{
  typedef long type;
  
  static const unsigned long long const_range = ULONG_MAX + 1;
  static const unsigned int const_bits = 32;
};

//---------------------------------------------------------------------------
#ifdef BOOST_HAS_LONG_LONG
template<>
struct integer_traits<long long> : boost::integer_traits<long long>
{
  typedef long long type;
  
  static const unsigned long long const_range = 18446744073709551615ULL;
  static const unsigned int const_bits = 64;
};
#endif //def BOOST_HAS_LONG_LONG
//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_INTEGER_TRAITS_HPP
