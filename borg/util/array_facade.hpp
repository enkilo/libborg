#ifndef BORG_UTIL_ARRAY_FACADE_HPP
#define BORG_UTIL_ARRAY_FACADE_HPP

#include <boost/mpl/if.hpp>
#include <sstream>
#include <algorithm>
#include "borg/range_predicate.hpp"
#include "borg/range_trunc.hpp"
#include "borg/skip_algorithms.hpp"
#include "borg/property_proxy.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>
#include <boost/bind/arg.hpp>
#include <iostream>

namespace borg {
namespace util {

class empty_base {};
using namespace boost;  
  
//! adapts standard containers to javascript-like array interface.
//----------------------------------------------------------------------------
template<class derived, class value, class base = derived, bool inherit = false>
class array_facade : public boost::mpl::if_<boost::mpl::bool_<inherit>, base, empty_base>::type
{
public:
  typedef derived derived_type;
  typedef value value_type;
  typedef base base_type;
  typedef array_facade<Derived, value, base, inherit> this_type;
  typedef typename base::const_iterator const_iterator;
  typedef typename base::const_reverse_iterator const_reverse_iterator;
  typedef typename base::iterator iterator;
  
  array_facade() :
    length(*static_cast<base_type *>(this),
           boost::mem_fn(&base_type::size),
           boost::bind(boost::mem_fn(&base_type::resize), _1, _2, value_type()))
  {}
  
  /// return length
/*  size_t
  length() const
  {
    return base_type::size();
  }*/
  
  /// push a value to the end of the array.
  value_type &
  push(const value_type &v)
  {
    base_type::push_back(v);
    return *--base_type::end();
  }
  
  /// pop a value from the end of the array.
  value_type
  pop()
  {
    return base_type::pop_back();
  }

  void
  pop(value_type &v)
  {
    v = base_type::pop_back();
  }

  /// unshift a value to the beginning of the array.
  value_type &
  unshift(const value_type &v)
  {
    base_type::push_front(v);
    return *base_type::begin();
  }
  
  /// remove the value at the beginning of the array and return it.
  value_type
  shift()
  {
    value_type ret = length() ? base_type::front() : value_type();
    base_type::pop_front();
    return ret;
  }
  
  void
  shift(value_type &v)
  {
    v = length() ? base_type::front() : value_type();
    base_type::pop_front();
  }  
  
  /// remove n elements beginning at element n.
  derived_type 
  splice(size_t s, size_t n)
  {
    derived_type ret;

    range_trunc(s, n, base_type::size());    
    ret.resize(n);
    
    iterator sit = skip_n(base_type::begin(), s);
    iterator eit = skip_n(sit, n);
    iterator rit = ret.begin();
    
    std::copy(sit, eit, rit);
    base_type::erase(sit, eit);
    
    return ret;
  }
  
  derived_type 
  splice(size_t s, size_t n, const value_type &v)
  {
    derived_type ret;

    range_trunc(s, n, base_type::size());    
    ret.resize(n);
    
    iterator sit = skip_n(base_type::begin(), s);
    iterator eit = skip_n(sit, n);
    iterator rit = ret.begin();
    
    std::copy(sit, eit, rit);
    base_type::erase(sit, eit);
//    base_type::insert(eit, v);
    
    return ret;
  }
  
  template<class SeparatorT>
  std::string
  join(const SeparatorT &sep) const
  {
    std::ostringstream os;
    
    if(!base_type::empty())
    {
      typename base_type::const_iterator it = base_type::begin();
      os << *it;

      while(++it != base_type::end())
      {
        os << sep;
        os << *it;
      }
    }
    return os.str(); 
  }
  
  std::string
  join() const
  {
    return join("");
  }
    
  int
  index_of(const value_type &v) const
  {
    size_t i = 0;
    const_iterator cit = base_type::begin();
    
    while(cit != base_type::end())
    {
      if(*cit == v)
        return i;
      
      ++i, ++cit;
    }
    return -1;
  }
  
  int
  last_index_of(const value_type &v) const
  {
    size_t i = base_type::size();
    const_reverse_iterator cit = base_type::rbegin();
    
    while(cit != base_type::rend())
    {
      --i;
      
      if(*cit == v)
        return i;

      ++cit;
    }
      
    return -1;
  }
  
  const value_type &
  operator[](size_t i) const
  {
    range_trunc(i, base_type::size());
    return *skip_n(base_type::begin(), i);
  }
  
  value_type &
  operator[](size_t i)
  {
    range_trunc(i, base_type::size());
    return *skip_n(base_type::begin(), i);
  }
  
  std::string
  to_string(char sep = ',') const
  {
    return join(sep);
  }
  
  std::string
  to_string(const std::string &sep) const
  {
    return join(sep);    
  }
  
  property_proxy<base_type, value_type> length;
};

} // namespace util
} // namespace borg

template<class derived, class value, class base, bool inherit, typename charT, class traits>
std::basic_ostream<charT, traits> &  
operator<<(std::basic_ostream<charT, traits> &os, 
           const borg::array_facade<Derived, value, base, inherit> &a)
{
  os << a.join(',');
  return os;
}
  
//---------------------------------------------------------------------------
#endif //ndef ARRAY_FACADE_HPP
