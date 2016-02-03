//----------------------------------------------------------------------------
//! \file  no_control_chars.hpp  
//! \brief Implements no_control_chars.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef NO_CONTROL_CHARS_HPP
#define NO_CONTROL_CHARS_HPP

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>

namespace io { namespace filter {

//----------------------------------------------------------------------------
template<typename Ch = char, int replace = '\0'>
class no_control_chars
{
public:
  typedef Ch char_type;
  struct category
    : boost::iostreams::dual_use
    , boost::iostreams::filter_tag 
  {};
  
  explicit no_control_chars()
  {}
  
  template<typename Sink>
  bool
  put(Sink &dest, int c)
  {
    if(c & 0xe0)
      return boost::iostreams::put(dest, c);
    else if(replace)
      return boost::iostreams::put(dest, replace);

    return true;
  }
  
  template<typename Sink>
  int
  get(Sink &dest)
  {
    int c = boost::iostreams::get(dest);
    
    if(c & 0xe0)
      return c;

    return replace;
  }
  
//private:
//  char_type const m_replace;
};

}} // namespace io::filter
//----------------------------------------------------------------------------
#endif //ndef NO_CONTROL_CHARS_HPP
