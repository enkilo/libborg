#ifndef VST_LOADER_HPP
#define VST_LOADER_HPP

#ifdef VSTSDK_INSTALLED
#include <vstsdk/aeffect.h>
#else
#include "pluginterfaces/vst2.x/aeffect.h"
#endif

#include "sys/rtld.hpp"

namespace vst {
 
//---------------------------------------------------------------------------
class loader : public sys::rtld
{
public:
  //! Type of the VSTPluginMain function...
  typedef AEffect *main_type(audioMasterCallback);
  
  loader(const std::string &path);
  virtual ~loader();
  
  main_type *
  get_main() const { return m_main; }
  
protected:
  main_type *m_main;
};
  
}// end of namespace wrap
//---------------------------------------------------------------------------
#endif //ndef VST_LOADER_HPP
