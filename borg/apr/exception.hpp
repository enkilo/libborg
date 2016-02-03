#ifndef BORG_APR_EXCEPTION_HPP
#define BORG_APR_EXCEPTION_HPP

#include <exception>
#include <string>
#include <apr_errno.h>
#include <borg/apr/traits.hpp>
#include <borg/util/exception.hpp>
#include <borg/error/exception.hpp>

namespace borg {
  
//---------------------------------------------------------------------------
template<>
class exception< apr::traits > : public std::exception
{
public:
  BORG_ERROR_EXCEPTION_TYPES( apr::traits )
  
 typedef borg::exception< apr::traits > this_type;
  
  static const size_type what_size = 128;
  
  explicit
  exception(const std::string &what) throw()
    : m_what(what)
  {}
  
  explicit
  exception(status_type st) throw()
  {
    m_what.resize(what_size, '\0');
    apr_strerror(st, const_cast<char *>(m_what.c_str()), 
                 m_what.max_size());
  }

  ~exception() throw() {}
  
private:
  std::string m_what;
};

namespace apr {
  
typedef borg::exception<traits> exception;
  
} // namespace apr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_APR_EXCEPTION_HPP
