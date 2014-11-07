#ifndef BORG_VSTGUI_TRAITS_HPP
#define BORG_VSTGUI_TRAITS_HPP

#include <vstgui/vstgui.h>

namespace borg {
namespace vstgui {

//---------------------------------------------------------------------------
struct traits
{
  typedef long          index_type;
  typedef const char   *string_type;
  typedef CDrawStyle    style_type;
  typedef CDrawContext  dc_type;
  typedef CView         widget_type;
  typedef CBitmap       bitmap_type;
  typedef CCoord        vector_type;
  typedef CPoint        point_type;
  typedef CRect         size_type;
  typedef CRect         rect_type;
  typedef unsigned char color_type;
  typedef CColor        rgba_type;
#if defined(WIN32) || defined(__MINGW32__)
  typedef CFontDesc     font_type;
#else
  typedef CFont         font_type;
#endif
  typedef long          align_type;
};

} // namespace vstgui
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef WX_TRAITS_HPP
