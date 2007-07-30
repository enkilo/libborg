#ifndef BORG_TK_BITMAP_HPP
#define BORG_TK_BITMAP_HPP

#include <borg/traits/vector_types.hpp>
#include <borg/traits/color_types.hpp>
#include <borg/wrap/wrapper.hpp>

namespace borg {
namespace tk {
  
//! Traits for wrapped bitmaps. 
//! Specialize this for every wrapped type.
//---------------------------------------------------------------------------
template<class toolkit>
struct bitmap_traits : 
  public traits::vector_types<typename toolkit::vector_type>,
  public traits::color_types<typename toolkit::color_type>
{
  typedef toolkit tk_type;
  typedef typename toolkit::dc_type dc_type;
  typedef typename toolkit::bitmap_type bitmap_type;
  typedef wrapper<bitmap_type> wrapper_type;
};

//! Use this inside your partial specialisations of the bitmap_adapter
//! template.
//---------------------------------------------------------------------------
#define BITMAP_TRAITS(Traits) \
  typedef Traits::tk_type tk_type; \
  typedef Traits::dc_type dc_type; \
  typedef Traits::bitmap_type bitmap_type; \
  typedef Traits::wrapper_type wrapper_type; \
  VECTOR_TRAITS(Traits::vector_type) \
  COLOR_TRAITS(Traits::color_type)

//---------------------------------------------------------------------------
#define BORG_TK_BITMAP_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, bitmap_type) \
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
    BORG_PP_USE_TYPE(Traits, align_type)
  
} // namespace tk
} // namespace borg

//---------------------------------------------------------------------------
#endif // BORG_TK_BITMAP_HPP
