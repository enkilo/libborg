#ifndef VSTGUI_WRAPPERS_HPP
#define VSTGUI_WRAPPERS_HPP

#include <vstgui/vstgui.h>

#include <borg/vstgui/traits.hpp>
//#include <interface/types.hpp>
#include <interface/dc.hpp>
//#include <tk/tk_wrappers.hpp>
/*#include <tk/bitmap_wrapper.hpp>
//#include <tk/widget_wrapper.hpp>*/
#include <borg/tk/traits.hpp>
#include <borg/tk/wrappers.hpp>

namespace borg {
namespace tk {  

//! Wraps VSTGUI::CDrawContext class into an implementation of abstract::dc.
template<>
class dc_wrapper<vstgui::traits>
    : public wrapper<vstgui::traits::dc_type *>
{
public:
  BORG_TK_DC_TYPES(vstgui::traits)
  
  typedef wrapper<dc_type *> wrapper_type;
    
  dc_wrapper(dc_type *dc) : wrapper_type(dc)
  {}

  ~dc_wrapper()
  {}
  
  #define DC_API(ret_type) inline ret_type
  #define DC_CALL(fn_call) wrapper_type::get()->fn_call;
  #define DC_CONST(c) const

  #include "borg/vstgui/dc.ipp"
  
  #undef DC_API
  #undef DC_CALL
};
  
//! Wraps VSTGUI::CView class into an implementation of abstract::widget.
template<>
class widget_wrapper<vstgui::traits>
    : public wrapper<vstgui::traits::widget_type *>
{
public:
  BORG_TK_DC_TYPES(vstgui::traits)

  typedef wrapper<widget_type *> wrapper_type;
    
  widget_wrapper(widget_type *w) 
      : wrapper_type(w)
  {}

  #define WIDGET_API(ret_type) inline ret_type
  #define WIDGET_CALL(fn_call) wrapper_type::get()->fn_call;

  #include "borg/vstgui/widget.ipp"
  
  #undef WIDGET_API
  #undef WIDGET_CALL
};

//! Wraps VSTGUI::CBitmap class into an implementation of abstract::bitmap.
template<>
class bitmap_wrapper<vstgui::traits>
    : public wrapper<vstgui::traits::bitmap_type *>
{
public:
  BORG_TK_DC_TYPES(vstgui::traits)

  typedef wrapper<bitmap_type *> wrapper_type;
    
  bitmap_wrapper(bitmap_type *b)
      : wrapper_type(b)
  {}

  #define BITMAP_API(ret_type) inline ret_type
  #define BITMAP_CALL(fn_call) wrapper_type::get()->fn_call;

  #include "borg/vstgui/bitmap.ipp"
  
  #undef BITMAP_API
  #undef BITMAP_CALL
};

} // namespace tk
} // namespace borg

#endif // VSTGUI_WRAPPERS_HPP
