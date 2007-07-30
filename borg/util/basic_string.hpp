#ifndef BORG_BASIC_STRING_HPP
#define BORG_BASIC_STRING_HPP

#include <string>
#include <cctype>

//#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/function.hpp>

#include <borg/util/basic_string_fwd.hpp>
#include <borg/util/array_fwd.hpp>
#include <borg/util/character_predicate.hpp>
#include <borg/util/property_proxy.hpp>

namespace borg {

namespace detail {  
TEMPLATE_CCC_PROPERTY(stdcxx::basic_string, 0, size_t, obj->size(), obj->set_size(value))
}
  
namespace stdcxx {

//----------------------------------------------------------------------------
template<class charT, class traits, class alloc>
class/* __attribute__((packed))*/ basic_string : public std::basic_string<charT, traits, alloc>
{
public:
  typedef std::basic_string<charT, traits, alloc> base_type;
  typedef borg::stdcxx::basic_string<charT, traits, alloc> this_type;
  typedef util::array<this_type> array_type;

  typedef typename base_type::allocator_type allocator_type;
  typedef typename base_type::size_type size_type;
  typedef typename base_type::value_type value_type;

  typedef typename base_type::iterator iterator;
  typedef typename base_type::const_iterator const_iterator;

  /// Construct an empty string using allocator a.
  basic_string(const allocator_type &a = allocator_type())
    : base_type(a)
    , length(this)
  {}

  /// Construct string with copy of value of \a str.
  basic_string(const base_type &str)
    : base_type(str)
    , length(this)
  {}

  /// Construct string as copy of a substring.
  basic_string(const base_type &str, size_type pos, size_type n = base_type::npos)
    : base_type(str, pos, n)
//    , length(offsetof(*this, length))
    , length(this)
  {}
  
  /// Construct string as copy of a substring.
  basic_string(const base_type &str, size_type pos, size_type n, const allocator_type &a)
    : base_type(str, pos, n, a)
//    , length(offsetof(*this, length))
    , length(this)
  {}
  
  /// Construct string initialized by a character array.
  basic_string(const value_type *s, const allocator_type &a = allocator_type())
    : base_type(s, a)
//    , length(offsetof(*this, length))
    , length(this)
  {}

  /// Construct string as multiple characters.
  basic_string(size_type n, value_type c = value_type(), const allocator_type &a = allocator_type())
    : base_type(n, c, a)
//    , length(offsetof(*this, length))
    , length(this)
  {}
  
  /// Construct string as copy of a range.
  template<class InputIterator>
  basic_string(InputIterator s, InputIterator e, const allocator_type &a = allocator_type())
    : base_type(s, e, a)
//    , length(offsetof(*this, length))
    , length(this)
  {}
  
  /// Empty destructor.
  ~basic_string()
  {}
  
  operator const char *() const
  {
    return base_type::c_str();
  }
  
  /// Camelize the string (this_is_a_string => thisIsAString).
  base_type &
  camelize(base_type &s) const;
  
  this_type 
  camelize() const
  {
    this_type ret;
    camelize(ret);
    return ret;
  }
  
  base_type &
  decamelize(base_type &s) const;
  
  this_type 
  decamelize() const
  {
    this_type ret;
    decamelize(ret);
    return ret;
  }
  
  bool
  equal(const charT *s)
  {
    return *this == s;
  }
  
  /// Split the string into an array of strings.
  util::array< this_type >
  split(const character_predicate<char> &sep = '\0', bool compress = true) const;
  
  /// Returns true if the string consists solely of uppercase characters.
  bool
  is_upper() const
  {
    const_iterator const e = base_type::end();
    const_iterator i = std::find_if(base_type::begin(), e, !boost::is_upper());
    return i == e;
  }
  
  /// Returns true if the string consists solely of lowercase characters.
  bool
  is_lower() const
  {
    const_iterator const e = base_type::end();
    const_iterator i = std::find_if(base_type::begin(), e, !boost::is_lower());
    return i == e;
  }
  
  /// Returns true if the string consists solely of whitespace characters.
  bool
  is_space() const
  {
    const_iterator const e = base_type::end();
    const_iterator i = std::find_if(base_type::begin(), e, !boost::is_space());
    return i == e;
  }
  
  /// Returns an uppercase version of the string.
  this_type  
  to_upper() const
  {
    this_type ret(base_type::length(), value_type());

    std::transform(base_type::begin(), base_type::end(), 
                   ret.begin(), boost::function<int(int)>(::toupper));
    return ret;
  }
  
  /// Returns a lowercase version of the string.
  this_type
  to_lower() const
  {
    this_type ret(base_type::length(), value_type());

    std::transform(base_type::begin(), base_type::end(),
                   ret.begin(), boost::function<int(int)>(::tolower));
    return ret;
  }
  
  /// Returns a version of the string having the first character uppercased.
  this_type
  ucfirst() const
  {
    this_type ret = *this;

    if(base_type::size())
    {
      iterator const i = ret.begin();
      *i = std::toupper(*i);
    }
    
    return ret;
  }

  size_t
  get_size() /*const*/
  {
//    std::cerr << "get_size() this=" << (void *)this << std::endl;
    return base_type::length();
  }
  
  void
  set_size(size_t n, value_type v = value_type())
  {
    iterator e = base_type::begin() + n;
    
    if(e < base_type::end())
      base_type::erase(e, base_type::end());

//    std::cerr << "resizing string (" << (void *)this << ") to: " << n << std::endl;
    base_type::resize(n, v);
  }
  
  TEMPLATE_CCC_PROPERTY_PROXY(::borg::detail, this_type, ::borg::stdcxx::basic_string, 0, size_t) length;
//  TEMPLATE_CCC_PROPERTY_PROXY(this_type, ::borg::basic_string, 0, size_t) length2;
};
  
//---------------------------------------------------------------------------
} // namespace stdcxx
} // namespace borg

#include <borg/util/array.hpp>

namespace borg {
namespace stdcxx {
  
//---------------------------------------------------------------------------
template<class charT, class traits, class alloc>
typename 
basic_string<charT, traits, alloc>::base_type &
basic_string<charT, traits, alloc>::camelize(base_type &s) const
{
  typedef typename base_type::const_iterator iterator_type;
  
  bool underscore = false;
  s.clear();
  
  for(iterator_type it = base_type::begin(); it != base_type::end(); ++it)
  {
    if(*it == '_')
      underscore = true;
    else
    {
      if(underscore)
      {
        s += std::toupper(*it);
        underscore = false;
      }
      else
        s += *it;
    }
  }
  
  return s;
}

//---------------------------------------------------------------------------
template<class charT, class traits, class alloc>
typename
basic_string<charT, traits, alloc>::array_type
basic_string<charT, traits, alloc>::split
    (const character_predicate<char> &sep, bool compress) const
{
  array_type ret;
  
  boost::algorithm::split
    (ret, *this, sep, (compress ? boost::token_compress_on
                                : boost::token_compress_off));
  return ret;
}  

//---------------------------------------------------------------------------
template<class charT, class traits, class alloc>
typename
basic_string<charT, traits, alloc>::base_type &
basic_string<charT, traits, alloc>::decamelize(base_type &s) const
{
  typedef typename base_type::const_iterator iterator_type;
  
  s.clear();
  
  for(iterator_type it = base_type::begin(); it != base_type::end(); ++it)
  {
    if(std::isupper(*it))
    {
      s += '_';
      s += std::tolower(*it);
    }
    else
      s += *it;
  }
  
  return s;
}
  
} // namespace stdcxx
} // namespace borg
//---------------------------------------------------------------------------
#endif //ndef BORG_BASIC_STRING_HPP
