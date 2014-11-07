#ifndef BORG_WX_DC_ADAPTER_HPP
#define BORG_WX_DC_ADAPTER_HPP

#include <wx/wx.h>

#include <borg/tk/dc.hpp>
#include <borg/tk/adapters_fwd.hpp>
#include <borg/tk/impl.hpp>
#include <borg/wx/traits.hpp>
#include <borg/wrap/wrapper_core_access.hpp>

//---------------------------------------------------------------------------
#warning "font crap?"
namespace borg {
namespace wx {

struct font
{
  wxFontFamily family;
  int size;
};

const font fonts[] =
{
  { wxFONTFAMILY_MODERN, 10 },
  { wxFONTFAMILY_SWISS, 24 },
  { wxFONTFAMILY_SWISS, 16 },
  { wxFONTFAMILY_SWISS, 12 },
  { wxFONTFAMILY_SWISS, 9 },
  { wxFONTFAMILY_SWISS, 7 }  
};

} // namespace wx
namespace tk {

//---------------------------------------------------------------------------
template<class Derived>
class dc_adapter< ::borg::wx::traits, Derived >
{
public:
  BORG_TK_DC_TYPES( ::borg::wx::traits )
    
  typedef Derived derived_type;

  #define DC_API(ret_type)    inline ret_type
  #define DC_CALL(fn_call)    DC_OBJ()->fn_call
  //#define DC_OBJ()            borg::wrapper_core_access::get(static_cast<derived_type const *>(this))
  #define DC_OBJ()            ((derived_type const *)(this))->get()
  #define DC_DEFAULT(def_val) = def_val
  #define DC_CONST(c)         const

  #include "borg/wx/dc_interface.ipp"

  #undef DC_API
  #undef DC_CALL
  #undef DC_OBJ
  #undef DC_CONST
};
  
} // namespace tk
namespace wx { 
  
//ADAPTER_ALIAS(traits, dc_adapter)

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif // BORG_WX_DC_ADAPTER_HPP
