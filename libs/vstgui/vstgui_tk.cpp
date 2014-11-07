#include <borg/vstgui/traits.hpp>
#include <borg/vstgui/vstgui_tk.hpp>
#include <borg/tk/widget.hpp>
#include <list>
//#include <iostream>
#include <borg/msg.hpp>

#if !defined(__MINGW32__) && !defined(WIN32)
#define kMouseEventNotHandled false
#define kMouseEventHandled true
#endif

namespace borg {
namespace tk {
  
//---------------------------------------------------------------------------
widget< ::borg::vstgui::traits >::~widget()
{
}

//---------------------------------------------------------------------------
void 
widget<vstgui::traits>::draw(CDrawContext *dc)
{
  drawRect(dc, getViewSize());
}    
    
//---------------------------------------------------------------------------
void 
widget<vstgui::traits>::drawRect(CDrawContext *dc, const CRect &rect)
{
  //std::cout << "widget<vstgui::traits>::drawRect()" << std::endl;
//  MSG_ERROR("widget<vstgui::traits>::drawRect(%p, %p)", dc, &rect);
  
  if(!onredraw.empty())
  {
    std::list<rect_type> rects;
    dc_wrapper<vstgui::traits> wrapped(dc);
    
    rects.push_back
      (rect_type(rect.x, rect.y, rect.width(), rect.height()));
       
    onredraw(*dc /*wrapped*/, rects);
  }
}

//---------------------------------------------------------------------------
void 
widget<vstgui::traits>::setViewSize(CRect &rect, bool invalid)
{
  CRect oldrect = getViewSize();


//  CView::setViewSize(rect, invalid);
  CView::setViewSize(rect);

  // position changed?
  if(oldrect.x != rect.x || oldrect.y != rect.y)
  {
    if(!onmove.empty())
      onmove(rect.x, rect.y);
  }

  // size changed? 
  if(oldrect.width() != rect.width() || oldrect.height() != rect.height())
  {
    if(!onresize.empty())
      onresize(rect.width(), rect.height());
  }
}

//---------------------------------------------------------------------------
CMouseEventResult
widget<vstgui::traits>::onMouseDown(CPoint &where, const long &buttons)
{
  event::mouse::button b = event::mouse::nobutton;
  
  if(buttons & kMButton) b = event::mouse::mbutton;
  if(buttons & kRButton) b = event::mouse::rbutton;
  if(buttons & kLButton) b = event::mouse::lbutton;
  
  return (onmousedown(where.x, where.y, b) ? 
          kMouseEventHandled : kMouseEventNotHandled);
}

//---------------------------------------------------------------------------
CMouseEventResult
widget<vstgui::traits>::onMouseUp(CPoint &where, const long &buttons)
{
  event::mouse::button b = event::mouse::nobutton;
  
  if(buttons & kMButton) b = event::mouse::mbutton;
  if(buttons & kRButton) b = event::mouse::rbutton;
  if(buttons & kLButton) b = event::mouse::lbutton;
  
  return (onmouseup(where.x, where.y, b) ? 
          kMouseEventHandled : kMouseEventNotHandled);
}

//---------------------------------------------------------------------------
CMouseEventResult
widget<vstgui::traits>::onMouseMoved(CPoint &where, const long &buttons)
{
  return kMouseEventHandled;
}

//---------------------------------------------------------------------------
CMouseEventResult
widget<vstgui::traits>::onMouseEntered(CPoint &where, const long &buttons)
{
  return kMouseEventHandled;
}

//---------------------------------------------------------------------------
CMouseEventResult
widget<vstgui::traits>::onMouseExited(CPoint &where, const long &buttons)
{
  return kMouseEventHandled;
}

//---------------------------------------------------------------------------
bool
widget<vstgui::traits>::onWheel(const CPoint &where, const float &distance, const long &buttons)
{
  return true;
}

} // namespace tk
} // namespace borg
