#ifndef BORG_TK_FRAME_HPP
#define BORG_TK_FRAME_HPP

#include <borg/tk/widget.hpp>

namespace borg {
namespace tk {
  
//! Traits for wrapped frames. 
//! Specialize this for every wrapped type.
//---------------------------------------------------------------------------
template<class toolkit>
struct frame_traits : 
  public widget_traits<toolkit>
{
  typedef typename toolkit::frame_type frame_type;
};

//! For use in classes where the traits are a template parameter.
//---------------------------------------------------------------------------
#define FRAME_TRAITS(Traits) \
  WIDGET_TRAITS(Traits) \
  typedef typename Traits::frame_type frame_type; 

//---------------------------------------------------------------------------
#define BORG_TK_FRAME_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, widget_type) \
    BORG_PP_USE_TYPE(Traits, dc_type) \
    BORG_PP_USE_TYPE(Traits, frame_type) \
    BORG_PP_USE_TYPE(Traits, point_type) \
    BORG_PP_USE_TYPE(Traits, size_type) \
    BORG_PP_USE_TYPE(Traits, rect_type) \
    BORG_PP_USE_TYPE(Traits, id_type) \
    BORG_PP_USE_TYPE(Traits, index_type) \
    BORG_PP_USE_TYPE(Traits, style_type) \
    BORG_PP_USE_TYPE(Traits, string_type)

} // namespace tk
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_TK_FRAME_HPP
