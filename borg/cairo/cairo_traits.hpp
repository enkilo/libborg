#ifndef CAIRO_TRAITS_HPP
#define CAIRO_TRAITS_HPP

#include <cairo/cairo.h>
#include <borg/types/rgba_type.hpp>
#include <borg/types/point_type.hpp>
#include <borg/types/size_type.hpp>
#include <borg/types/rect_type.hpp>

namespace borg {
namespace cairo {
  
struct traits
{
  typedef double              vector_type;
  typedef double              color_type;
  typedef cairo_t            *dc_type;
  typedef cairo_surface_t    *widget_type;
  typedef cairo_surface_t    *bitmap_type;
  typedef borg::point<double> point_type;
  typedef borg::size<double>  size_type;
  typedef borg::rect<double>  rect_type;
  typedef borg::rgba<double>  rgba_type;
  typedef const char         *string_type;
  typedef int                 index_type;
  typedef long                style_type;
  typedef void               *font_type; //FIXME?
  typedef int                 align_type;
};
  
} // namespace cairo
} // namespace borg

#endif //ndef CAIRO_TRAITS_HPP
