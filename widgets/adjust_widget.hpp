#ifndef ADJUST_WIDGET_HPP
#define ADJUST_WIDGET_HPP

//#include <interface/types.hpp>
//#include <tk/widget_wrapper.hpp>
//#include <cairo/cairo_tk.hpp>

//---------------------------------------------------------------------------
namespace widgets {

using namespace std;
using namespace event;
using tk::widget;

//---------------------------------------------------------------------------
template<typename toolkit>
  class adjust : public widget<toolkit>
{
public:
  typedef typename widget<toolkit>::traits traits;

  WIDGET_TRAITS(traits)
  
  adjust(const wrapper_type &parent, const rect_type &size, const char *fmt, float value = 0.0f) :
    widget<toolkit>(parent, size)
  {
//      onredraw.connect(event::bind_method(&adjust<tk_type>::redraw, this));
    dispatch::widget<toolkit>::onfocusgain.bind(&adjust<toolkit>::focus, this);
    dispatch::widget<toolkit>::onfocusloose.bind(&adjust<toolkit>::focus, this);
    dispatch::widget<toolkit>::onredraw.bind(&adjust<toolkit>::redraw, this);
    dispatch::widget<toolkit>::onmousedown.bind(&adjust<toolkit>::mousedown, this);
    dispatch::widget<toolkit>::onmouseup.bind(&adjust<toolkit>::mouseup, this);
  }
  
  virtual ~adjust() {}
  
protected:
  float m_value;
  const char *m_fmt;
  bool m_focus;
  bool m_adjust;

  bool focus(bool f) 
  {
    m_focus = f; 
    std::cout << (f ? "gains" : "looses") << " focus" << std::endl; 
    return true;
  }

  bool redraw(const dc_wrapper &dc, const list<rect_type> &rects)
  {
    rect_type r;
    widget<toolkit>::size(r);

    dc.set_stroke_color(0, 0, 0);

    if(m_adjust)
      dc.set_fill_color(255, 0, 0);
    else
      dc.set_fill_color(255, 255, 0);

    dc.draw_rect(r);
    dc.draw_text("test", r, align_center);
    
    ::cairo::paint_dc cdc(dc);
    
    cdc.set_stroke_color(0, 255, 255);
    cdc.draw_ellipse(r);

    return true;
  }

  bool mousedown(const vector_type &x, const vector_type &y, mouse::button)
  {
    std::cout << "adjust::mousedown" << std::endl;
    m_adjust = true;
    widget<toolkit>::set_dirty();
    return true;
  }

  bool mouseup(const vector_type &x, const vector_type &y, mouse::button)
  {
    std::cout << "adjust::mouseup" << std::endl;
    m_adjust = false;
    widget<toolkit>::set_dirty();
    return true;
  }
};

} // namespace widgets
//---------------------------------------------------------------------------
#endif // ADJUST_WIDGET_HPP
