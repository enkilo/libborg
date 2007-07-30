#warning "obsolete"
#ifndef VST_EDITOR_HPP
#define VST_EDITOR_HPP

#include <types/size_type.hpp>
#include <public.sdk/source/vst2.x/aeffeditor.h>
#include <vst/plugin.hpp>

namespace vst {
 
  class editor : public AEffEditor
  {
  public:
    editor(plugin &plugin, const std::size<int> &sz);
    virtual ~editor();
    
    bool isOpen();
    bool getRect(ERect **erect);

  protected:
    std::size<int> m_size;
    ERect m_rect;
    bool m_opened;
  };

} // end of namespace wrap
#endif // VST_EDITOR_HPP
