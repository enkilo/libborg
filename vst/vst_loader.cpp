#include <vst/vst_loader.hpp>

namespace vst {

//-------------------------------------------------------------------
loader::loader(const std::string &path) : rtld(path)
{
  if(is_open())
  {
    m_main = sym<vst::loader::main_type *>("VSTPluginMain");
    if(m_main == 0)
      close();
  }
}

//-------------------------------------------------------------------
loader::~loader()
{
  close();
}  

//-------------------------------------------------------------------
} // end of namespace vst
