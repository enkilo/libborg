#ifndef BORG_WX_WIDGET_HPP
#define BORG_WX_WIDGET_HPP

#include <wx/wx.h>

#include <borg/tk/impl.hpp>
#include <borg/wx/widget_adapter.hpp>
#include <borg/event/dispatch.hpp>

namespace borg {
namespace tk {

using namespace ::tk;
  
//---------------------------------------------------------------------------
template<>
class widget< wx::traits > 
    : public wxWindow
    , public widget_adapter<
        wx::traits,
        widget< wx::traits >
      >
    , public event::dispatch::widget< wx::traits >
{
public:
  BORG_TK_WIDGET_TYPES( wx::traits )
  
  widget(widget_type &parent, const point_type &pos, const size_type &sz) :
    wxWindow(&parent, wxID_ANY, pos, sz)
  {}

  widget(widget_type &parent, const rect_type &dim) :
    wxWindow(&parent, wxID_ANY, dim.GetPosition(), dim.GetSize())
  {}
  
  widget(widget_type &parent, id_type id = wx::default_id,
         const point_type &pos = wx::default_position,
         const size_type &size = wx::default_size,
         long style = 0,
         const wxString &name = "wx::widget") :
    wxWindow(&parent, id, pos, size, style, name)
  {}

  virtual ~widget();
  
  const wxWindow *get() const { return this; }
  wxWindow *get() { return this; }

private:
  DECLARE_EVENT_TABLE()
      
  bool m_dirty;
    
  void OnFocusSet(wxFocusEvent &event);
  void OnFocusKill(wxFocusEvent &event);
  void OnMove(wxMoveEvent &event);
  void OnSize(wxSizeEvent &event);
  void OnMouseUp(wxMouseEvent &event);
  void OnMouseDown(wxMouseEvent &event);
  void OnMouseDClick(wxMouseEvent &event);
  void OnMouseMove(wxMouseEvent &event);
  void OnMouseWheel(wxMouseEvent &event);
  void OnPaint(wxPaintEvent &event);
};

} // namespace tk
namespace wx {
  
  typedef tk::widget<traits> widget;

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_WIDGET_HPP
