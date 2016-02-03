#ifndef VST_WXEDITOR_HPP
#define VST_WXEDITOR_HPP

#include <wx/wx.h>
#include <vst/vst_plugin.hpp>
#include <vst/vst_editor.hpp>

namespace vst {

  class wxeditor : public editor
  {
  public:
    wxeditor(vst::plugin &vstplugin, const borg::size<int> &sz);
    virtual ~wxeditor();
    
    bool open(void *ptr);
    void close();
    bool OnInit();
    
#ifdef WIN32
    static bool init(HINSTANCE hInst);
    static void shutdown();
#endif //ndef WIN32

  protected:
    wxPanel *frame;
  };

} // end of namespace wrap
#endif // VST_WXEDITOR_HPP
