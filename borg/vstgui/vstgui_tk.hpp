#ifndef VSTGUI_TK_HPP
#define VSTGUI_TK_HPP

#include <borg/tk/wrappers.hpp>
#include <borg/tk/impl.hpp>
#include <borg/vstgui/vstgui_wrappers.hpp>
#include <borg/event/dispatch.hpp>

namespace borg {
namespace tk {

//! Instantiable vstgui draw context.
template<>
class paint_dc<vstgui::traits> 
    : public CDrawContext
    , public dc_wrapper<vstgui::traits>
{
public:
  paint_dc(CFrame *frame, void *sysctx, void *window) :
    CDrawContext(frame, sysctx, window),
    dc_wrapper<vstgui::traits>(this)
  {}
};

template<>
class client_dc<vstgui::traits> 
  : public CDrawContext
  , public dc_wrapper<vstgui::traits>
{
public:
  client_dc(CFrame *frame, void *sysctx, void *window) :
    CDrawContext(frame, sysctx, window),
    dc_wrapper<vstgui::traits>(this)
  {}
};

//! Instantiable vstgui widget.
template<>
class widget<vstgui::traits> 
  : public CView
  , public widget_wrapper<vstgui::traits>
  , public event::dispatch::widget<vstgui::traits>
{
public:
  typedef vstgui::traits tk_type;
  typedef widget_wrapper<vstgui::traits> widget_type;
  typedef event::dispatch::widget<vstgui::traits> event_type;
  typedef widget_type::rect_type rect_type;
  typedef widget_type::rgba_type rgba_type;
  
  widget(const CRect &size) :
    CView(size), widget_wrapper<vstgui::traits>(this)
  {}

  virtual ~widget();

  //! Those should be called internally by the widget container
  //! when redrawing is needed.
  void draw(CDrawContext *dc);
  void drawRect(CDrawContext *dc, const CRect &rect);

#if !defined(WIN32) && !defined(__MINGW32__)
#define CMouseEventResult bool
#endif
  
  void setViewSize(CRect &rect, bool invalid = true);
  CMouseEventResult onMouseDown(CPoint &where, const long &buttons);
  CMouseEventResult onMouseUp(CPoint &where, const long &buttons);
  CMouseEventResult onMouseMoved(CPoint &where, const long &buttons);
  CMouseEventResult onMouseEntered(CPoint &where, const long &buttons);
  CMouseEventResult onMouseExited(CPoint &where, const long &buttons);
  bool onWheel(const CPoint &where, const float &distance, const long &buttons);
};

}; // end of namespace tk

namespace vstgui {

using namespace tk;  
typedef paint_dc<vstgui::traits> paint_dc;
typedef client_dc<vstgui::traits> client_dc;
 // typedef dc_wrapper_traits<vstgui::traits>::dc_type dc_type;

//  typedef widget<vstgui::traits> widget;
} // namespace vstgui
} // namespace borg

#endif // VSTGUI_TK_HPP
