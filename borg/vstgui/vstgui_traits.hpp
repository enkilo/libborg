#warning "obsolete"
#ifndef VSTGUI_TRAITS_HPP
#define VSTGUI_TRAITS_HPP

#include <vstgui/vstgui.h>

namespace tk {
  
struct vstgui_traits
{
  typedef CCoord vector_type;
  typedef unsigned char color_type;
  typedef CDrawContext *dc_type;
  typedef CView *widget_type;
  typedef CBitmap *bitmap_type;
};
  
} // namespace tk
#endif //ndef VSTGUI_TRAITS_HPP
