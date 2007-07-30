#include <borg/wx/tk.hpp>
#include <borg/msg.hpp>

namespace borg {
namespace tk {

BEGIN_EVENT_TABLE(widget<wx::traits>, wxWindow)
  EVT_SET_FOCUS(widget<wx::traits>::OnFocusSet)  
  EVT_KILL_FOCUS(widget<wx::traits>::OnFocusKill)
  EVT_MOVE(widget<wx::traits>::OnMove)
  EVT_SIZE(widget<wx::traits>::OnSize)
  EVT_PAINT(widget<wx::traits>::OnPaint)
  EVT_LEFT_DOWN(widget<wx::traits>::OnMouseDown)
  EVT_RIGHT_DOWN(widget<wx::traits>::OnMouseDown)
  EVT_MIDDLE_DOWN(widget<wx::traits>::OnMouseDown)
  EVT_LEFT_UP(widget<wx::traits>::OnMouseUp)
  EVT_RIGHT_UP(widget<wx::traits>::OnMouseUp)
  EVT_MIDDLE_UP(widget<wx::traits>::OnMouseUp)
  //  EVT_CLOSE(wxtestFrame::OnClose)
  
  EVT_LEFT_DCLICK(widget<wx::traits>::OnMouseDClick)
  EVT_RIGHT_DCLICK(widget<wx::traits>::OnMouseDClick)
  EVT_MIDDLE_DCLICK(widget<wx::traits>::OnMouseDClick)
  EVT_MOUSEWHEEL(widget<wx::traits>::OnMouseWheel)
  EVT_MOTION(widget<wx::traits>::OnMouseMove)
END_EVENT_TABLE()

//----------------------------------------------------------------------------

widget<wx::traits>::~widget()
{
}
  
//----------------------------------------------------------------------------
void 
widget<wx::traits>::OnFocusSet(wxFocusEvent &event)
{
  if(!onfocusgain.empty())
    onfocusgain(true);
}

//----------------------------------------------------------------------------
void 
widget<wx::traits>::OnFocusKill(wxFocusEvent &event)
{
  if(!onfocusloose.empty())
    onfocusloose(false);
}

//----------------------------------------------------------------------------
void 
widget<wx::traits>::OnPaint(wxPaintEvent &event)
{
  if(!onredraw.empty())
  {
    // Find Out where the window is scrolled to
//    int vbX,vbY;   // Top left corner of client
    
//    GetViewStart(&vbX,&vbY);
    wxRegionIterator upd(GetUpdateRegion());  // get the update rect list
    
    std::list<rect_type> rects;
    
    while(upd)
    {
      wxRect rect(upd.GetRect());
      rects.push_back(rect_type(rect.GetX(), rect.GetY(), 
                                rect.GetWidth(), rect.GetHeight()));
      upd++;
    }
    
    wx::paint_dc dc(*this);
    onredraw(*dc.get(), rects);
  }
  
  m_dirty = false;
}

//----------------------------------------------------------------------------
void 
widget<wx::traits>::OnMove(wxMoveEvent &event)
{
  wxPoint position = event.GetPosition();
  
  if(!onmove.empty())
    onmove(position.x, position.y);
}

//----------------------------------------------------------------------------
void 
widget<wx::traits>::OnSize(wxSizeEvent &event)
{
  wxSize size = event.GetSize();
  
  if(!onresize.empty())
    onresize(size.GetWidth(), size.GetHeight());
}

//----------------------------------------------------------------------------
void 
widget<wx::traits>::OnMouseUp(wxMouseEvent &event)
{
  event::mouse::button b = event::mouse::nobutton;
  
  switch(event.GetButton())
  {
    case wxMOUSE_BTN_LEFT: b = event::mouse::lbutton; break;
    case wxMOUSE_BTN_MIDDLE: b = event::mouse::mbutton; break;
    case wxMOUSE_BTN_RIGHT: b = event::mouse::rbutton; break;
  }
  
  if(!onmouseup.empty())
    onmouseup(event.GetX(), event.GetY(), b);
}

//----------------------------------------------------------------------------
void
widget<wx::traits>::OnMouseDown(wxMouseEvent &event)
{
  event::mouse::button b = event::mouse::nobutton;
  
  switch(event.GetButton())
  {
    case wxMOUSE_BTN_LEFT: b = event::mouse::lbutton; break;
    case wxMOUSE_BTN_MIDDLE: b = event::mouse::mbutton; break;
    case wxMOUSE_BTN_RIGHT: b = event::mouse::rbutton; break;
  }
  
  if(!onmousedown.empty())
    onmousedown(event.GetX(), event.GetY(), b);
}

//----------------------------------------------------------------------------
void
widget<wx::traits>::OnMouseDClick(wxMouseEvent &event)
{
  event::mouse::button b = event::mouse::nobutton;
  
  switch(event.GetButton())
  {
    case wxMOUSE_BTN_LEFT: b = event::mouse::lbutton; break;
    case wxMOUSE_BTN_MIDDLE: b = event::mouse::mbutton; break;
    case wxMOUSE_BTN_RIGHT: b = event::mouse::rbutton; break;
  }
  
  if(!onmousedown.empty())
    onmousedown(event.GetX(), event.GetY(), b);
}

//----------------------------------------------------------------------------
void
widget<wx::traits>::OnMouseMove(wxMouseEvent &event)
{
  int b = 0;
  
  if(event.LeftIsDown()) b |= event::mouse::lbutton;
  if(event.MiddleIsDown()) b |= event::mouse::mbutton;
  if(event.RightIsDown()) b |= event::mouse::rbutton;
  
  // somehow it seems to fall into a false assertion when no slots are connected?
  if(!onmousemove.empty())
    onmousemove(event.GetX(), event.GetY(), b);
}

void widget<wx::traits>::OnMouseWheel(wxMouseEvent &event)
{
}


} // end of namespace tk
} // end of namespace borg
