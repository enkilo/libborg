#ifndef CAIRO_DC_HPP
#define CAIRO_DC_HPP

#include <borg/tk/wrappers.hpp>
#include <borg/tk/dc.hpp>
#include <borg/cairo/cairo_traits.hpp>
#include <borg/types/alignment_type.hpp>
#include <borg/types/draw_style.hpp>
#include <borg/iconv.hpp>

namespace borg {
namespace cairo {

struct font
{
  const char *family;
  double size;
};
  
const struct font fonts[] =
{
  { "Courier New", 14 },
  { "Bitstream Vera Sans Mono", 16 },
  { "Bitstream Vera Sans", 36 },
  { "Bitstream Vera Sans", 24 },
  { "Bitstream Vera Sans", 16 },
  { "Bitstream Vera Sans", 10 },
  { "Bitstream Vera Sans", 10 },
};

} // namespace cairo
namespace tk {

using borg::point;
using borg::rect;
using borg::rgba;

using namespace types;
  
//! Wraps cairo_t class into an implementation of drawable.
template<>
struct dc_wrapper<cairo::traits>
    : public wrapper<cairo::traits::dc_type>
{
  BORG_TK_DC_TYPES( cairo::traits )
  
  typedef wrapper<dc_type> wrapper_type;
    
  dc_wrapper(cairo_t *__cairo = 0) :
    wrapper_type(__cairo),
    m_surface(0),
    m_stroke(0, 0, 0)
  {
    if(wrapper_type::get() == 0)
      wrapper_type::set(cairo_create(m_surface));
    
    m_drawstyle = draw_stroked;

    cairo_set_line_width(wrapper_type::get(), 1.0);
    cairo_set_line_cap(wrapper_type::get(), CAIRO_LINE_CAP_ROUND);      
  }
    
  dc_wrapper(cairo_surface_t *__surface, cairo_t *__cairo = 0) :
    wrapper_type(__cairo),
    m_surface(__surface),
    m_stroke(0, 0, 0)
  {
    if(wrapper_type::get() == 0)
      wrapper_type::get() = cairo_create(m_surface);
    
    m_drawstyle = draw_stroked;
    
    cairo_set_line_width(wrapper_type::get(), 1.0);
    cairo_set_line_cap(wrapper_type::get(), CAIRO_LINE_CAP_ROUND);
  }
  
#define DC_API(ret_type)    inline ret_type
#define DC_OBJ              wrapper_type::get()
#define DC_DEFAULT(def_val) = def_val
#define DC_PROT(def)

#include "borg/cairo/cairo_dc.ipp"

#undef DC_API
#undef DC_OBJ
#undef DC_DEFAULT
#undef DC_PROT

private:
  cairo_surface_t *m_surface;
  point<vector_type> m_penloc;
  rect<vector_type> m_clip;
  rgba<color_type> m_stroke;
  rgba<color_type> m_fill;
  rgba<color_type> m_text;
//  font_type m_font;
  int m_drawstyle;
  double m_strokewidth;
  int m_fonttype;
  int m_fontstyle;
  double m_fontsize;

};

} // namespace tk
namespace cairo {

typedef tk::dc_wrapper<traits> dc;

} // namespace cairo
} // namespace borg

#endif // CAIRO_DC_HPP
