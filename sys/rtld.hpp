#ifndef SYS_RTLD_HPP
#define SYS_RTLD_HPP

#include <string>
#include <dlfcn.h>

namespace sys {

class rtld
{
public:
  rtld();
  rtld(const std::string &path);
  ~rtld();

  bool is_open() const { return m_handle != 0; }
    
  bool open(const std::string &path);
  void close();
  
  template<typename symbolT>
  symbolT sym(const std::string &symbol)
  {
    return (symbolT)(dlsym(m_handle, symbol.c_str()));
  }
  
protected:
  void *m_handle;
};

} // end of namespace sys
#endif // SYS_RTLD_HPP
