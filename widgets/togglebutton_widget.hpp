#ifndef TOGGLEBUTTON_WIDGET_HPP
#define TOGGLEBUTTON_WIDGET_HPP

#include <borg/cairo/cairo_tk.hpp>

//---------------------------------------------------------------------------
namespace borg {
namespace tk {

using namespace std;
using namespace event;
using tk::widget;

//---------------------------------------------------------------------------
template<class Traits>

class togglebutton
    : public widget<Traits>
{
public:
  BORG_TK_WIDGET_TYPES(typename Traits)

  togglebutton(widget_type &parent, const rect_type &size, const string_type &text) :
    tk::widget<Traits>(parent, size)
  {
//      events::onredraw.connect(event::bind_method(&togglebutton<Traits>::redraw, this));
//      events::onfocusgain.bind(&togglebutton<Traits>::focus, this);
//      events::onfocusloose.bind(&togglebutton<Traits>::focus, this);
    dispatch::widget<Traits>::onredraw.bind(&togglebutton<Traits>::redraw, this);
    dispatch::widget<Traits>::onmousedown.bind(&togglebutton<Traits>::mousedown, this);
//      events::onmouseup.bind(&togglebutton<Traits>::mouseup, this);
  }
  
  virtual ~togglebutton() {}
  
protected:
  float m_value;
  const char *m_fmt;
  bool m_focus;
  bool m_toggle;

  bool focus(bool f) 
  {
    m_focus = f; 
    std::cout << (f ? "gains" : "looses") << " focus" << std::endl; 
    return true;
  }

  bool redraw(dc_type &dc, list<rect_type> const &rects)
  {
    rect_type r;
    borg::tk::widget<Traits>::get_rect(r);

    borg::tk::dc_wrapper<Traits> mydc(&dc);
    
    mydc.set_stroke_color(0, 0, 0);

    if(m_toggle)
      mydc.set_fill_color(255, 0, 0);
    else
      mydc.set_fill_color(255, 255, 0);

    mydc.draw_rect(r);
    mydc.draw_text("test", r, align_center);
    
    cairo::paint_dc cdc(mydc);
    
    cairo::traits::rect_type cr(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight());
    
    cdc.set_stroke_color(1.0, 1.0, 1.0, 1.0);
    cdc.draw_ellipse(cr);

    return true;
  }

  bool mousedown(vector_type const &x, vector_type const &y, mouse::button)
  {
    std::cout << "togglebutton::mousedown" << std::endl;
    m_toggle = !m_toggle;
    
    tk::widget<Traits>::refresh();
//    tk::widget<Traits>::set_dirty();
    return true;
  }

/*    bool mouseup(const vector_type &x, const vector_type &y, mouse::button)
  {
    std::cout << "togglebutton::mouseup" << std::endl;
    m_toggle = false;
    tk::widget<Traits>::set_dirty();
    return true;
  }*/
};

} // namespace tk
} // namespace borg

//---------------------------------------------------------------------------
#endif // TOGGLEBUTTON_WIDGET_HPP
