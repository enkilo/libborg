#warning "obsolete"
#ifndef VSTGUI_DC_ADAPTER_HPP
#define VSTGUI_DC_ADAPTER_HPP

#include <vstgui/vstgui.h>
#include "vstgui/vstgui_traits.hpp"
#include <borg/tk/dc_traits.hpp>
#include "interface/dc.hpp"

//! Implements our generic drawcontext interface ontop vstgui.
template<
    class derived,
    class traits
>
class dc_adapter
{
public:
  DC_TRAITS(traits)
    
  typedef derived const derived_type;

  #define DC_API(ret_type)    inline ret_type
  #define DC_CALL(fn_call)    DC_OBJ()->fn_call;
  #define DC_OBJ()            static_cast<derived_type *>(this)->get()
  #define DC_CONST(c)         const

  #include "vstgui/vstgui_dc.ipp"
  
  #undef DC_API
  #undef DC_CALL
  #undef DC_OBJ
};
  
} // end of namespace vstgui
//---------------------------------------------------------------------------
#endif // VSTGUI_DC_ADAPTER_HPP
