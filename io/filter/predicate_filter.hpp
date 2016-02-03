//----------------------------------------------------------------------------
//! \file  predicate_filter.hpp  
//! \brief Implements predicate_filter.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef PREDICATE_FILTER_HPP
#define PREDICATE_FILTER_HPP

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>

namespace io { namespace filter {

//----------------------------------------------------------------------------
template<typename PredicateT, typename Ch = char>
class predicate_filter
{
public:
  typedef Ch char_type;
  struct category
    : boost::iostreams::output_filter_tag 
  {};
  
  explicit 
  predicate_filter(const PredicateT &pred)
    : m_predicate(pred)
  {}
  
  template<typename Sink>
  bool
  put(Sink &dest, int c)
  {
    if(m_predicate(char_type(c)))
      return true;

    return boost::iostreams::put(dest, c);
  }

private:
  PredicateT m_predicate;
};

}// namespace io::filter

//----------------------------------------------------------------------------
template<typename PredicateT>
filter::predicate_filter<PredicateT>
filter_if(const PredicateT &p)
{
  return filter::predicate_filter<PredicateT>(p);
}

//----------------------------------------------------------------------------
template<typename PredicateT>
filter::predicate_filter<PredicateT>
pass_if(const PredicateT &p)
{
  return filter::predicate_filter<PredicateT>(!p);
}
  
} // namespace io
//----------------------------------------------------------------------------
#endif //ndef PREDICATE_FILTER_HPP
