#ifndef BORG_TK_DC_HPP
#define BORG_TK_DC_HPP

//---------------------------------------------------------------------------
#include <boost/integer_traits.hpp>
#include <borg/tk/fwd.hpp>
#include <borg/traits/color_types.hpp>
#include <borg/traits/vector_types.hpp>
#include <borg/types/draw_style.hpp>
#include <borg/types/font_style.hpp>
#include <borg/types/alignment_type.hpp>

namespace borg {
namespace tk {

//! Types used inside dc_adapter specialisations.
//---------------------------------------------------------------------------
template<class toolkit>
struct dc_traits : 
  public traits::vector_types<typename toolkit::vector_type>,
  public traits::color_types<typename toolkit::color_type>
{
  typedef toolkit tk_type;
  typedef typename toolkit::dc_type dc_type;
  typedef wrapper<dc_type> wrapper_type;
  
  typedef types::draw_style draw_style;
  typedef types::font_style font_style;
//  typedef types::font_type font_type;
/*  typedef tk::bitmap_traits<toolkit> bitmap_traits;
  typedef typename bitmap_traits::bitmap_type bitmap_type;
  typedef typename bitmap_traits::bitmap_wrapper bitmap_wrapper;*/
};

//! For use in classes where the traits are a template parameter.
//---------------------------------------------------------------------------
#define DC_TRAITS(_dc_traits) \
  typedef _dc_traits dc_traits; \
  typedef typename dc_traits::tk_type tk_type; \
  typedef typename dc_traits::dc_type dc_type; \
  typedef typename dc_traits::wrapper_type wrapper_type; \
  \
  typedef typename dc_traits::draw_style draw_style; \
  typedef typename dc_traits::font_style font_style; \
  \
  VECTOR_TRAITS(typename dc_traits::vector_type) \
  COLOR_TRAITS(typename dc_traits::color_type)

//---------------------------------------------------------------------------
#define BORG_TK_DC_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, widget_type) \
    BORG_PP_USE_TYPE(Traits, dc_type) \
    BORG_PP_USE_TYPE(Traits, vector_type) \
    BORG_PP_USE_TYPE(Traits, point_type) \
    BORG_PP_USE_TYPE(Traits, size_type) \
    BORG_PP_USE_TYPE(Traits, rect_type) \
    BORG_PP_USE_TYPE(Traits, color_type) \
    BORG_PP_USE_TYPE(Traits, rgba_type) \
    BORG_PP_USE_TYPE(Traits, index_type) \
    BORG_PP_USE_TYPE(Traits, string_type) \
    BORG_PP_USE_TYPE(Traits, style_type) \
    BORG_PP_USE_TYPE(Traits, font_type) \
    BORG_PP_USE_TYPE(Traits, align_type) \
    BORG_PP_USE_TYPE(Traits, bitmap_type)


} // namespace tk
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_TK_DC_HPP
