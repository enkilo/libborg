#include <vst/vst_editor.hpp>
#include <borg/msg.hpp>

namespace vst {

//-------------------------------------------------------------------
editor::editor(plugin &plugin, const borg::size<int> &sz) :
  AEffEditor(&plugin),
  m_size(sz),
  m_opened(false)
{
  m_rect.left = 0;
  m_rect.top = 0;
  m_rect.right = sz.w();
  m_rect.bottom = sz.h();

  effect->setEditor(this);
  MSG_BOX("effect->setEditor(%p)", this);
}
  
//-------------------------------------------------------------------
editor::~editor()
{
  effect->setEditor(0);
}

//-------------------------------------------------------------------
bool editor::isOpen()
{
  MSG_BOX("isOpen()");
  return m_opened;
}
  
//-------------------------------------------------------------------
bool editor::getRect(ERect **erect)
{
  MSG_BOX("getRect(%p)", erect);
  
  *erect = &m_rect;
  return true;
}  

//-------------------------------------------------------------------
} // end of namespace vst
