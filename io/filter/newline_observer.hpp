//----------------------------------------------------------------------------
//! \file  newline_observer.hpp  
//! \brief Implements indent_output_filter.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef NEWLINE_OBSERVER_HPP
#define NEWLINE_OBSERVER_HPP

#include <boost/iostreams/filter/newline.hpp>

namespace io { namespace filter {

using namespace boost::iostreams;
  
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
template<typename CatchPolicy>
class newline_observer : public CatchPolicy
{
public:
  typedef char char_type;
  
  explicit
  indent_output(char indent_char = ' ', int target = newline::mixed) :
    m_char(indent_char),
    m_target(target)
  {
    if(target != newline::posix &&
       target != newline::dos &&
       target != newline::mac &&
       target != newline::mixed)
    {
      throw std::logic_error("bad flags");
    }
  }
};

//----------------------------------------------------------------------------

}} // namespace io::filter
//----------------------------------------------------------------------------
#endif //ndef NEWLINE_OBSERVER_HPP
