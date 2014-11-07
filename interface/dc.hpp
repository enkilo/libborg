#ifndef INTERFACE_DC_HPP
#define INTERFACE_DC_HPP

#include <interface/macros.hpp>
#include <borg/types/point_type.hpp>
#include <borg/types/rect_type.hpp>
#include <borg/types/rgba_type.hpp>
#include <boost/integer_traits.hpp>

namespace abstract 
{
//! Draw Style.
  enum draw_style
  {
    draw_transparent = 0,
    draw_stroked = 1,
    draw_filled = 2,
    draw_stroked_and_filled = 3
  };

  //! Font Type
  enum font_type
  {
    font_fixed,
    font_very_big,
    font_big,
    font_medium,
    font_small,
    font_very_small,
  };

  //! Font Styles
  enum font_style
  {
    font_normal = 0,
    font_bold = 1,
    font_italic = 2,
    font_bold_and_italic = 3
  };

  //! Horizontal Text Alignment
  enum text_align
  {
    align_left = 1,
    align_right = 2,
    align_center = 3,
    align_horizontal = 3,
      
    align_top = 4,
    align_bottom = 8,
    align_middle = 12,
    align_vertical = 12,
  };

#define dc_TYPEDEF(vector, color) \
  typedef vector vector_type; \
  typedef std::point<vector_type> point_type; \
  typedef borg::rect<vector_type> rect_type; \
  \
  typedef color color_type; \
  typedef borg::rgba<color_type> rgba_type; 

//! Generic interface to 2D draw context.
/*  template<typename vectorT, typename colorT>
    class dc
  {
  public:
    dc_TYPEDEF(vectorT, colorT)

    #define DC_API(ret_type) inline ret_type
    
    #include <interface/dc.ipp>
      
    #undef DC_API
  };*/
  
} // end of namespace abstract  
#endif // INTERFACE_DC_HPP

