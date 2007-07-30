#ifndef VST_EDITOR_HPP
#define VST_EDITOR_HPP

#include <borg/types/size_type.hpp>

#ifdef VSTSDK_INSTALLED
#include <vstsdk/aeffeditor.h>
#else
#include "public.sdk/source/vst2.x/aeffeditor.h"
#endif

#include <vst/vst_plugin.hpp>

namespace vst {
 
class editor : public AEffEditor
{
public:
  editor(plugin &plugin, const borg::size<int> &sz);
  virtual ~editor();
    
  bool isOpen();
  bool getRect(ERect **erect);
  
protected:
  borg::size<int> m_size;
  ERect m_rect;
  bool m_opened;
};

} // end of namespace wrap
#endif // VST_EDITOR_HPP
