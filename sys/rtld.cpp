extern "C"
{
#include <dlfcn.h>
}

#include <sys/rtld.hpp>

namespace sys {

//---------------------------------------------------------------------------
rtld::rtld() : m_handle(0)
{
}  

//---------------------------------------------------------------------------
rtld::~rtld()
{
  if(m_handle)
    close();
}  
    
//---------------------------------------------------------------------------
rtld::rtld(const std::string &path)
{
  m_handle = dlopen(path.c_str(), RTLD_NOW);
}  

//---------------------------------------------------------------------------
bool rtld::open(const std::string &path)
{
  if(m_handle == 0)
  {
    m_handle = dlopen(path.c_str(), RTLD_NOW);
    if(m_handle) return true;
  }
  return false;
}  

//---------------------------------------------------------------------------
void rtld::close()
{
  if(m_handle)
    dlclose(m_handle);
  m_handle = 0;
}
  
//---------------------------------------------------------------------------
/*void *rtld::sym(const std::string &symbol)
{
  return dlsym(m_handle, symbol.c_str());
}*/
  
//---------------------------------------------------------------------------
} // end of namespace sys
