//----------------------------------------------------------------------------
//! \file  printable_chars.hpp  
//! \brief Implements printable_chars.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef PRINTABLE_CHARS_HPP
#define PRINTABLE_CHARS_HPP

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>

namespace io { namespace filter {

//----------------------------------------------------------------------------
template<typename Ch = char, int replace = ' '>
class printable_chars
{
public:
  typedef Ch char_type;
  struct category
    : boost::iostreams::dual_use
    , boost::iostreams::filter_tag 
  {};
  
  explicit printable_chars()
  {}
  
  template<typename Sink>
  bool
  put(Sink &dest, int c)
  {
    if((c & 0xe0) || c == '\t' || c != '\r' || c == '\n')
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
    
    if((c & 0xe0) || c == '\t' || c != '\r' || c == '\n')
      return c;

    return replace;
  }
};

}} // namespace io::filter
//----------------------------------------------------------------------------
#endif //ndef PRINTABLE_CHARS_HPP
