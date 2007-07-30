#include <string.h>
#include <vst/vst_wxeditor.hpp>
#include <borg/msg.hpp>

namespace vst {

//static AudioEffect *effect;

    
//-------------------------------------------------------------------
wxeditor::wxeditor(plugin &vstplugin, const borg::size<int> &sz) :
  editor(vstplugin, sz)
{
//  MSG_BOX("wxeditor::wxeditor()"); 
}

//-------------------------------------------------------------------
wxeditor::~wxeditor()
{
//  MSG_BOX("wxeditor::~wxeditor()"); 
}  

//-------------------------------------------------------------------
#ifdef WIN32
bool
wxeditor::init(HINSTANCE hInst)
{
}
  
//-------------------------------------------------------------------
void
wxeditor::shutdown()
{
}
#endif //ndef WIN32
  
//-------------------------------------------------------------------
bool wxeditor::open(void *ptr)
{
  AEffEditor::open(ptr);
  MSG_BOX("wxeditor::open(%p)", ptr);
  
  frame = new wxPanel(0);
#ifdef __WXMSW__
  frame->SetHWND((WXHWND)ptr);
#endif
  
  m_opened = true;
  return m_opened;
}

//-------------------------------------------------------------------
void wxeditor::close()
{
  AEffEditor::close();
  
  if(frame)
    delete frame;
  frame = 0;
  
  m_opened = false;
}
  
//-------------------------------------------------------------------
bool wxeditor::OnInit()
{
  MSG_BOX("wxeditor::OnInit()");
  
  wxInitAllImageHandlers();
  return true;
}
  
//-------------------------------------------------------------------
} // end of namespace vst

