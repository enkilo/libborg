#ifndef BORG_WX_FRAME_HPP
#define BORG_WX_FRAME_HPP

#include <wx/wx.h>
#include <string>

#include <borg/wx.hpp>
#include <borg/tk/impl.hpp>
#include <borg/wx/frame_adapter.hpp>
#include <borg/event/dispatch.hpp>

namespace borg {
namespace tk {

//---------------------------------------------------------------------------
template<>
class frame< ::borg::wx::traits > 
    : public wxFrame
    , public tk::frame_adapter<
         ::borg::wx::traits ,
        frame< ::borg::wx::traits >
      >
    , public event::dispatch::widget< ::borg::wx::traits >
{
public:
  BORG_TK_FRAME_TYPES(  ::borg::wx::traits  )

//  typedef tk::frame_traits< ::borg::wx::traits >::widget_type widget_type;
//  FRAME_TRAITS(frame_traits< ::borg::wx::traits >)
//  WIDGET_TRAITS(frame_traits< ::borg::wx::traits >)
  
  frame(id_type id = wx::default_id,
        const string_type &title = "wx::frame",
        const point_type &pos = wx::default_position,
        const size_type &size = wx::default_size,
        long style = wx::default_frame_style,
        const string_type &name = "wx::frame") :
    wxFrame(0, id, title, pos, size, style, name)
  {}

  frame(widget_type &parent, id_type id = wx::default_id,
        const string_type &title = "wx::frame",
        const point_type &pos = wx::default_position,
        const size_type &size = wx::default_size,
        long style = wx::default_frame_style,
        const string_type &name = "wx::frame") :
    wxFrame(&parent, id, title, pos, size, style, name)
  {}

  virtual ~frame();
  
  const wxFrame *get() const { return this; }
  wxFrame *get() { return this; }

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
  typedef tk::frame<traits> frame; 
} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_FRAME_HPP
