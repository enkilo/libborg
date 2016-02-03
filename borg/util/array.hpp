#ifndef BORG_UTIL_ARRAY_HPP
#define BORG_UTIL_ARRAY_HPP

#include <list>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <borg/util/array_adapter.hpp>
#include <borg/util/string.hpp>

namespace borg {
namespace util {
  
//---------------------------------------------------------------------------
template<class ValueT>
//class array : public array_adapter< array<ValueT>, ValueT, std::list<ValueT>, true >
class array 
  : public std::list<ValueT>
  , public borg::util::array_adapter< array<ValueT>, ValueT, std::list<ValueT> >
{
public:
  typedef array<ValueT> this_type;
  typedef std::list<ValueT> base_type;
  typedef borg::util::array_adapter<this_type, ValueT> adapter_type;
  
  typedef typename base_type::value_type value_type;
  typedef typename base_type::pointer pointer;
  typedef typename base_type::const_pointer const_pointer;
  typedef typename base_type::reference reference;
  typedef typename base_type::const_reference const_reference;

  typedef typename base_type::iterator iterator;
  typedef typename base_type::const_iterator const_iterator;
  typedef typename base_type::reverse_iterator reverse_iterator;
  typedef typename base_type::const_reverse_iterator const_reverse_iterator;

  typedef typename base_type::size_type size_type;
  typedef typename base_type::difference_type difference_type;
  typedef typename base_type::allocator_type allocator_type;

  explicit
  array(const allocator_type &a = allocator_type())
    : base_type(a)
  {}

  array(size_type n, const value_type &v = value_type(), 
        const allocator_type &a = allocator_type()) 
    : base_type(n, v, a)
  {}
  
  array(const base_type &base) 
    : base_type(base)
  {}

  template<typename InputIterator>
  array(InputIterator first, InputIterator last, 
        const allocator_type &a = allocator_type())
    : base_type(first, last, a)
  {}
  
  const ValueT &
  item(size_t i) const { return base_type::operator[](i); }

  ValueT &
  item(size_t i) { return base_type::operator[](i); }
  
  void
  resize(size_type n, value_type v = value_type())
  {
    return base_type::resize(n, v);
  }
  
};
  

} // namespace util
} // namespace borg

template<class T, class CharT, class Traits>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os, const borg::util::array<T> &arr)
{
  os << arr.join(',');
  return os;
}

template<class T, class CharT, class Traits>
std::basic_istream<CharT, Traits> &
operator>>(std::basic_istream<CharT, Traits> &is, borg::util::array<T> &arr)
{
  T v;
  CharT sep;
  
  do
  {
    is >> v;
    
    arr.push_back(v);
    
    is >> sep;
  }
  while(sep == ',');
  
  return is;
}

//---------------------------------------------------------------------------
namespace boost {
namespace program_options {

//---------------------------------------------------------------------------  
//! This will allow the use of the array template class together with
//! boost::program_options.
//---------------------------------------------------------------------------  
template<class T>
inline static void
validate(any &v, const std::vector<std::string> &values,
         borg::util::array<T> *args, int)
{
  if(v.empty())
    v = any(borg::util::array<T>());

  borg::util::array<T> *av = any_cast< borg::util::array<T> >(&v);

  for(unsigned i = 0; i < values.size(); ++i)
  {
    try {
      av->push_back(lexical_cast<T>(values[i]));
    }
    catch(const bad_lexical_cast &e) {
      throw_exception(invalid_option_value(values[i]));
    }
  }
}
  
} // namespace program_options
} // namespace boost
    
//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_ARRAY_HPP
