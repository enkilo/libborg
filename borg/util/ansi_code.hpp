#ifndef BORG_UTIL_ANSI_CODE_HPP
#define BORG_UTIL_ANSI_CODE_HPP

#include <string>
#include <list>
#include <cctype>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <borg/string/char_traits.hpp>
#include <borg/util/ansi_color.hpp>
#include <borg/util/bind_method.hpp>

namespace borg {

//using namespace std;
//using namespace boost;

//----------------------------------------------------------------------------
namespace ansi {
  
enum cmd
{
  cmd_color = 'm',
};
  
//----------------------------------------------------------------------------
enum attr
{
  attr_none = -1,
  attr_normal = 0,
  attr_bold = 1,
};

enum fgcolor
{
  fgnd_black   = 30,
  fgnd_red     = 31,
  fgnd_green   = 32,
  fgnd_yellow  = 33,
  fgnd_blue    = 34,
  fgnd_magenta = 35,
  fgnd_cyan    = 36,
  fgnd_white   = 37
};
  
enum bgcolor
{
  bgnd_black   = 40,
  bgnd_red     = 41,
  bgnd_green   = 42,
  bgnd_yellow  = 43,
  bgnd_blue    = 44,
  bgnd_magenta = 45,
  bgnd_cyan    = 46,
  bgnd_white   = 47,
};
  
} // namespace ansi
  
typedef ansi::cmd ansi_cmd;
typedef ansi::attr ansi_attr;
typedef ansi::fgcolor ansi_fgcolor;
typedef ansi::bgcolor ansi_bgcolor;
  
//----------------------------------------------------------------------------
class malformed_ansi_sequence : public std::exception
{
public:
  explicit malformed_ansi_sequence() : m_what("malformed ansi code") {}
  virtual ~malformed_ansi_sequence() throw() {}
  const char *what() const throw() { return m_what.c_str(); }

private:
  std::string m_what;
};
  
//---------------------------------------------------------------------------
template<
  typename CharT = char,
  typename Traits = std::char_traits<CharT>
>
class ansi_sequence_separator
{
public:
  ansi_sequence_separator(CharT &cmdchar) : m_cmdchar(cmdchar) {}
  
  template<typename InputIterator, typename Token>
  bool operator()(InputIterator &next, InputIterator end, Token &tok)
  {
    int n = 0;
    bool ret = false;
    
    while(isdigit(*next))
    {
      n *= 10;
      n += *next - '0';
      ++next;
      ret = true;
    }

    if(ret == true)
    {
      if((m_cmdchar = *next) == ';')
        ++next;
   
      tok = n;
    }

    return ret;
  }
  
  void reset() {}
  int cmdchar() const { return m_cmdchar; }
  
private:
  CharT &m_cmdchar;
};  
  
//---------------------------------------------------------------------------
template<
  typename CharT = char,
  typename Traits = std::char_traits<CharT>
>
class ansi_sequence
{
public:
  // default constructor
  explicit
  ansi_sequence() : m_cmd(-1)
  {}
  
  // construct from escape, sequence and command
  explicit
  ansi_sequence(CharT cmd, const std::vector<int> &seq = std::vector<int>()) :
    m_seq(seq), m_cmd(cmd)
  {}

  // construct from given command and codes
  explicit
  ansi_sequence(CharT cmd, int seq1) : m_cmd(cmd)
  {
    m_seq.push_back(seq1);
  }

  explicit
  ansi_sequence(CharT cmd, int seq1, int seq2) : m_cmd(cmd)
  {
    m_seq.push_back(seq1);
    m_seq.push_back(seq2);
  }

  explicit
  ansi_sequence(CharT cmd, int seq1, int seq2, int seq3) : m_cmd(cmd)
  {
    m_seq.push_back(seq1);
    m_seq.push_back(seq2);
    m_seq.push_back(seq3);
  }

  // create ansi code by parsing from string
  template<template<class, class> class Tmpl>
  ansi_sequence(const Tmpl< CharT, std::char_traits<CharT> > &ansi) : m_cmd(-1)
  {
    std::string::size_type bpos;
    
    if((bpos = ansi.find('[')) == ansi.length())
      throw malformed_ansi_sequence();
    
    typedef boost::tokenizer<
        ansi_sequence_separator<CharT, Traits>,
        typename Tmpl< CharT, std::char_traits<CharT> >::const_iterator,
        int 
    > ansi_tokenizer;
    
    // 2nd argument is implicitly constructed ansi_sequence_separator
    ansi_tokenizer toks(ansi.substr(bpos + 1), m_cmd);
    
    for_each(toks.begin(), toks.end(), bind_method(&std::vector<int>::push_back, m_seq));
  }
  
  // get/set the command
  void cmd(CharT c) { m_cmd = c; }
  CharT cmd() const { return m_cmd; }
  
  // get the sequence
  const std::vector<int> &
  seq() const { return m_seq; }

  std::vector<int> &
  seq() { return m_seq; }
  
  // add a number to the sequence
  ansi_sequence &
  add(int n) { m_seq.push_back(n); return *this; }
  
  // explicit conversion to string
  std::basic_string<CharT>
  to_string(const std::basic_string<CharT> &escape = "\033") const
  {
    std::basic_ostringstream<CharT> ret;
    std::vector<int>::const_iterator it = m_seq.begin();

    ret << escape << '[';
    
    for(;;)
    {      
      ret << (*it);
      
      if(++it == m_seq.end())
        break;
      
      ret << ';';
    }

    if(m_cmd != -1)
      ret << CharT(m_cmd);

    return ret.str();
  }

  // implicit conversion to string
  operator std::string() const
  {
    return to_string();
  }
  
private:
  std::vector<int> m_seq;
  int m_cmd;
};
  
inline static ansi_sequence<>
ansi_color_code(int a1)
{
  return ansi_sequence<>('m', a1);
}

inline static ansi_sequence<>
ansi_color_code(int a1, int a2)
{
  return ansi_sequence<>('m', a1, a2);
}

inline static ansi_sequence<>
ansi_color_code(ansi_color const &fg, ansi_color const &bg, int a3)
{
  return ansi_sequence<>('m', fg.scalar(), bg.scalar(), a3);
}

#ifndef __GCCXML__
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os, const borg::ansi_sequence<CharT> &ansi)
{
  os << ansi.to_string();
  return os;
}  
#endif
  
} // namespace borg
//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_ANSI_CODE_HPP
