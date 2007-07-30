#ifndef BORG_UTIL_EXCEPTION_HPP
#define BORG_UTIL_EXCEPTION_HPP

#include <exception>
#include <borg/string.hpp>

namespace borg {

//---------------------------------------------------------------------------
template<class Traits>
class exception : public std::exception
{
public:
//  typedef string<typename Traits::wchar_type, Traits> string_type;
  typedef std::string string_type;
  
  explicit
  exception(string_type const &what) throw() : m_what(what) {}
  ~exception() throw() {}
  
  const char *
  what() const throw() { return m_what.c_str(); }
  
protected:
  explicit
  exception() throw() {}  
  
  string_type m_what;
};

}// namespace borg
//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_EXCEPTION_HPP
