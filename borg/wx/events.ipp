#include <borg/wx/dc.hpp>

BEGIN_EVENT_TABLE(EVENTS_CLASS, EVENTS_BASE)
  EVT_SET_FOCUS(EVENTS_CLASS::OnFocusSet)  
  EVT_KILL_FOCUS(EVENTS_CLASS::OnFocusKill)
  EVT_MOVE(EVENTS_CLASS::OnMove)
  EVT_SIZE(EVENTS_CLASS::OnSize)
  EVT_PAINT(EVENTS_CLASS::OnPaint)
  EVT_LEFT_DOWN(EVENTS_CLASS::OnMouseDown)
  EVT_RIGHT_DOWN(EVENTS_CLASS::OnMouseDown)
  EVT_MIDDLE_DOWN(EVENTS_CLASS::OnMouseDown)
  EVT_LEFT_UP(EVENTS_CLASS::OnMouseUp)
  EVT_RIGHT_UP(EVENTS_CLASS::OnMouseUp)
  EVT_MIDDLE_UP(EVENTS_CLASS::OnMouseUp)
  //  EVT_CLOSE(wxtestFrame::OnClose)
  
  EVT_LEFT_DCLICK(EVENTS_CLASS::OnMouseDClick)
  EVT_RIGHT_DCLICK(EVENTS_CLASS::OnMouseDClick)
  EVT_MIDDLE_DCLICK(EVENTS_CLASS::OnMouseDClick)
  EVT_MOUSEWHEEL(EVENTS_CLASS::OnMouseWheel)
  EVT_MOTION(EVENTS_CLASS::OnMouseMove)
END_EVENT_TABLE()

//----------------------------------------------------------------------------
void 
EVENTS_CLASS::OnFocusSet(wxFocusEvent &event)
{
  if(!onfocusgain.empty())
    onfocusgain(true);
}

//----------------------------------------------------------------------------
void 
EVENTS_CLASS::OnFocusKill(wxFocusEvent &event)
{
  if(!onfocusloose.empty())
    onfocusloose(false);
}

//----------------------------------------------------------------------------
void 
EVENTS_CLASS::OnPaint(wxPaintEvent &event)
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
    onredraw(*(wxDC *)dc.get(), rects);
  }
  
  m_dirty = false;
}

//----------------------------------------------------------------------------
void 
EVENTS_CLASS::OnMove(wxMoveEvent &event)
{
  wxPoint position = event.GetPosition();
  
  if(!onmove.empty())
    onmove(position.x, position.y);
}

//----------------------------------------------------------------------------
void 
EVENTS_CLASS::OnSize(wxSizeEvent &event)
{
  wxSize size = event.GetSize();
  
  if(!onresize.empty())
    onresize(size.GetWidth(), size.GetHeight());
}

//----------------------------------------------------------------------------
void 
EVENTS_CLASS::OnMouseUp(wxMouseEvent &event)
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
EVENTS_CLASS::OnMouseDown(wxMouseEvent &event)
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
EVENTS_CLASS::OnMouseDClick(wxMouseEvent &event)
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
EVENTS_CLASS::OnMouseMove(wxMouseEvent &event)
{
  int b = 0;
  
  if(event.LeftIsDown()) b |= event::mouse::lbutton;
  if(event.MiddleIsDown()) b |= event::mouse::mbutton;
  if(event.RightIsDown()) b |= event::mouse::rbutton;
  
  // somehow it seems to fall into a false assertion when no slots are connected?
  if(!onmousemove.empty())
    onmousemove(event.GetX(), event.GetY(), b);
}

void EVENTS_CLASS::OnMouseWheel(wxMouseEvent &event)
{
}
