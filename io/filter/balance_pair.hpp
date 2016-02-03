//----------------------------------------------------------------------------
//! \file  balance_pair.hpp  
//! \brief Implements balance_pair.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef BALANCE_PAIR_HPP
#define BALANCE_PAIR_HPP

#include <boost/iostreams/filter/newline.hpp>
#include <io/filter/detail/indentation_state.hpp>
#include <string>
#include <cctype>

namespace io { namespace filter {

using namespace boost;
  
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class balance_pair : public iostreams::output_filter
{
  using std::string;
  using std::isspace;
  
public:
  explicit
  balance_pair(char const indent_char = ' ', 
               bool const leading_space = true) :
    m_indent(indent_char),
    m_leading_space(leading_space),
    m_newline(true),
    m_state(0)
  {}
  
  template<typename Sink>
  bool
  put(Sink &dest, int c)
  {
    using iostreams::newline::CR;
    using iostreams::newline::LF;
    
    if(c == CR || c == LF)
      m_newline = true;

    else if(m_newline)
    {
      if(m_leading_space == false)
      {
        if(isspace(c))
          return true;
      }
      
      m_newline = false;
      
      for(int i = 0; i < m_state; ++i)
      {
        if(iostreams::put(dest, m_indent) == false)
          return false;
      }
    }

    return iostreams::put(dest, c);    
  }
  
  template<typename Sink>
  void 
  close(Sink &dest)
  {
    m_newline = true;
    m_state = 0;
  }
  
  detail::indentation_state &
  state()
  {
    return m_state;
  }
  
private:
  char const m_indent;
  bool const m_leading_space;
  bool m_newline;
  detail::indentation_state m_state;
};

//----------------------------------------------------------------------------
BOOST_IOSTREAMS_PIPABLE(balance_pair, 0)

}} // namespace io::filter
//----------------------------------------------------------------------------
#endif //ndef BALANCE_PAIR_HPP
