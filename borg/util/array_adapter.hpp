#ifndef BORG_UTIL_ARRAY_ADAPTER_HPP
#define BORG_UTIL_ARRAY_ADAPTER_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <sstream>
#include <algorithm>
#include <borg/util/array_fwd.hpp>
#include <borg/util/range_predicate.hpp>
#include <borg/util/range_trunc.hpp>
#include <borg/util/skip_algorithms.hpp>
#include <borg/util/property_proxy.hpp>
#include <borg/util/detail/property_impl.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>
#include <boost/bind/arg.hpp>
#include <iostream>

namespace borg {
namespace util {

class empty_base {};

#ifndef DERIVED_CAST
#define DERIVED_CAST(d) static_cast<Derived *>(d)
#endif
  
#ifndef CONST_DERIVED_CAST
#define CONST_DERIVED_CAST(d) static_cast<Derived const *>(d)
#endif
  
//----------------------------------------------------------------------------
template<class Derived, class value, class base = Derived, bool inherit = false>
class array_adapter;

} // namespace util
  
namespace detail {
  
TEMPLATE_CCCB_PROPERTY(util::array_adapter, 0, size_t, obj->get_size(), obj->set_size(value))
  
} // namespace detail
namespace util {
  
//! adapts standard containers to javascript-like array interface.
//----------------------------------------------------------------------------
template<class Derived, class ValueT, class base, bool inherit>
class array_adapter : public boost::mpl::if_<boost::mpl::bool_<inherit>, base, empty_base>::type
{
public:
  typedef Derived derived_type;
  typedef ValueT value_type;
  typedef base base_type;
  typedef array_adapter<Derived, ValueT, base, inherit> this_type;
  typedef typename base_type::const_iterator const_iterator;
  typedef typename base_type::const_reverse_iterator const_reverse_iterator;
  typedef typename base_type::iterator iterator;
  
  array_adapter() : length(this)/* :
    length(*DERIVED_CAST(this),
           boost::mem_fn(&base_type::size),
           boost::bind(boost::mem_fn(&Derived::resize), _1, _2, value_type()))*/
  {}
  
  //-------------------------------------------------------------------------
  /// return length
  //-------------------------------------------------------------------------
/*  size_t
  length() const
  {
    return base_type::size();
  }*/
  
  //-------------------------------------------------------------------------
  /// push a value to the end of the array.
  //-------------------------------------------------------------------------
  value_type &
  push(const value_type &v)
  {
    DERIVED_CAST(this)->push_back(v);
    return *--DERIVED_CAST(this)->end();
  }
  
  //-------------------------------------------------------------------------
  /// pop a value from the end of the array.
  //-------------------------------------------------------------------------
  value_type
  pop()
  {
    return DERIVED_CAST(this)->pop_back();
  }

  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  void
  pop(value_type &v)
  {
    v = DERIVED_CAST(this)->pop_back();
  }

  //-------------------------------------------------------------------------
  /// unshift a value to the beginning of the array.
  //-------------------------------------------------------------------------
  value_type &
  unshift(const value_type &v)
  {
    DERIVED_CAST(this)->push_front(v);
    return *DERIVED_CAST(this)->begin();
  }
  
  //-------------------------------------------------------------------------
  /// remove the value at the beginning of the array and return it.
  //-------------------------------------------------------------------------
  value_type
  shift()
  {
    value_type ret = DERIVED_CAST(this)->size() ? DERIVED_CAST(this)->front() : value_type();
    DERIVED_CAST(this)->pop_front();
    return ret;
  }
  
  void
  shift(value_type &v)
  {
    v = DERIVED_CAST(this)->size() ? DERIVED_CAST(this)->front() : value_type();
    DERIVED_CAST(this)->pop_front();
  }  
  
  //-------------------------------------------------------------------------
  /// remove all elements beginning at element n.
  //-------------------------------------------------------------------------
  derived_type 
  tail(size_t s)
  {
    derived_type ret;

    range_trunc(s, DERIVED_CAST(this)->size());    
    ret.resize(DERIVED_CAST(this)->size() - s);
    
    iterator sit = skip_n(DERIVED_CAST(this)->begin(), s);
    iterator const eit = DERIVED_CAST(this)->end();
    iterator rit = ret.begin();
    
    std::copy(sit, eit, rit);
//    DERIVED_CAST(this)->erase(sit, eit);
    
    return ret;
  }

  derived_type 
  splice(size_t s, size_t n)
  {
    derived_type ret;

    range_trunc(s, n, DERIVED_CAST(this)->size());    
    ret.resize(n);
    
    iterator sit = skip_n(DERIVED_CAST(this)->begin(), s);
    iterator eit = skip_n(sit, n);
    iterator rit = ret.begin();
    
    std::copy(sit, eit, rit);
    DERIVED_CAST(this)->erase(sit, eit);
    
    return ret;
  }
  
  derived_type 
  splice(size_t s, size_t n, const value_type &v)
  {
    derived_type ret;

    range_trunc(s, n, DERIVED_CAST(this)->size());    
    ret.resize(n);
    
    iterator sit = skip_n(DERIVED_CAST(this)->begin(), s);
    iterator eit = skip_n(sit, n);
    iterator rit = ret.begin();
    
    std::copy(sit, eit, rit);
    DERIVED_CAST(this)->erase(sit, eit);
    
    return ret;
  }
  
  //-------------------------------------------------------------------------
  /// Join the array members into a string stream, using the specified 
  /// separator.
  //-------------------------------------------------------------------------
  template<class SeparatorT>
  std::string
  join(const SeparatorT &sep) const
  {
    std::ostringstream os;
    
//    if(!base_type::empty())
    if(!CONST_DERIVED_CAST(this)->empty())
    {
      typename base_type::const_iterator it =
        CONST_DERIVED_CAST(this)->begin();

      os << *it;

      while(++it != CONST_DERIVED_CAST(this)->end())
      {
        os << sep;
        os << *it;
      }
    }
    return os.str(); 
  }
  
  //-------------------------------------------------------------------------
  /// Join the array members into a string stream, using no separator.
  //-------------------------------------------------------------------------
  std::string
  join() const
  {
    return join("");
  }
    
  //-------------------------------------------------------------------------
  /// Search array members for a value. Returns index of the first match or
  /// -1.
  //-------------------------------------------------------------------------
  int
  index_of(const value_type &v) const
  {
    size_t i = 0;
    const_iterator cit = DERIVED_CAST(this)->begin();
    
    while(cit != DERIVED_CAST(this)->end())
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
    size_t i = CONST_DERIVED_CAST(this)->size();
    const_reverse_iterator cit = CONST_DERIVED_CAST(this)->rbegin();
    
    while(cit != CONST_DERIVED_CAST(this)->rend())
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
    range_trunc(i, CONST_DERIVED_CAST(this)->size());
    return *skip_n(CONST_DERIVED_CAST(this)->begin(), i);
  }
  
  value_type &
  operator[](size_t i)
  {
    if(i >= DERIVED_CAST(this)->size())
    {
      try { DERIVED_CAST(this)->resize(i + 1); }
      catch(...)
      {
//        length.set(0);
        throw;
      }
    }
      
//    range_trunc(i, DERIVED_CAST(this)->size());
    return *skip_n(DERIVED_CAST(this)->begin(), i);
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

  size_t 
  get_size() const
  {
    return CONST_DERIVED_CAST(this)->size();
  }
  
  void
  set_size(size_t n, value_type v = value_type())
  {
    return DERIVED_CAST(this)->resize(n, v);
  }
  
  template<class PredicateFn>
  util::array<typename boost::function_traits<PredicateFn>::result_type>
  map(PredicateFn *fn)
  {
    util::array<typename boost::function_traits<PredicateFn>::result_type> ret;
    iterator it = DERIVED_CAST(this)->begin();
    
    while(it != DERIVED_CAST(this)->end())
    {
      ret.push_back(fn(*it));
      ++it;
    }

    return ret;
  }
  
  TEMPLATE_CCCB_PROPERTY_PROXY(::borg::detail, this_type, ::borg::util::array_adapter, 0, size_t) length;
//  property_proxy<base_type, value_type> length;
};

} // namespace util
} // namespace borg

template<class Derived, class value, class base, bool inherit, typename charT, class traits>
std::basic_ostream<charT, traits> &  
operator<<(std::basic_ostream<charT, traits> &os, 
           const borg::util::array_adapter<Derived, value, base, inherit> &a)
{
  os << a.join(',');
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_ARRAY_ADAPTER_HPP
