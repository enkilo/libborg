#ifndef BORG_TK_WIDGET_HPP
#define BORG_TK_WIDGET_HPP

#include <borg/traits/vector_types.hpp>
#include <borg/traits/color_types.hpp>
#include <borg/tk/fwd.hpp>
#include <borg/preproc.hpp>
#include <borg/wrap/preproc.hpp>

namespace borg {
namespace tk {
  
//! Traits for wrapped widgets. 
//! Specialize this for every wrapped type.
template<class toolkit>
struct widget_traits : 
  public traits::vector_types<typename toolkit::vector_type>,
  public traits::color_types<typename toolkit::color_type>
{
  typedef toolkit tk_type;
  typedef typename toolkit::widget_type widget_type;
  typedef wrapper<widget_type *> wrapper_type;
  typedef typename toolkit::dc_type dc_type;
  typedef ::borg::tk::dc_wrapper<toolkit> wrapped_dc;

//  typedef typename wrapper::wrap_traits wrapper_traits;
//  typedef dc_traits<toolkit, dc_type> dc_traits;
//  typedef widget_wrapper<toolkit> widget_type;
};

#define WIDGET_TRAITS(_widget_traits) \
  typedef _widget_traits widget_traits; \
  typedef typename widget_traits::widget_type widget_type; \
  typedef typename widget_traits::wrapper_type wrapper_type; \
  typedef typename widget_traits::dc_type dc_type; \
  typedef typename widget_traits::wrapped_dc wrapped_dc; \
  VECTOR_TRAITS(typename widget_traits::vector_type) \
  COLOR_TRAITS(typename widget_traits::color_type)

// TODO: 
WRAP_PATTERN_FORWARD(widget)
  
//---------------------------------------------------------------------------
#define BORG_TK_WIDGET_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, widget_type) \
    BORG_PP_USE_TYPE(Traits, dc_type) \
    BORG_PP_USE_TYPE(Traits, vector_type) \
    BORG_PP_USE_TYPE(Traits, point_type) \
    BORG_PP_USE_TYPE(Traits, size_type) \
    BORG_PP_USE_TYPE(Traits, rect_type) \
    BORG_PP_USE_TYPE(Traits, color_type) \
    BORG_PP_USE_TYPE(Traits, rgba_type) \
    BORG_PP_USE_TYPE(Traits, id_type) \
    BORG_PP_USE_TYPE(Traits, index_type) \
    BORG_PP_USE_TYPE(Traits, style_type) \
    BORG_PP_USE_TYPE(Traits, string_type)

} // namespace tk
} // namespace borg

//---------------------------------------------------------------------------
#endif // BORG_TK_WIDGET_HPP
