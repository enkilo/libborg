#ifndef BORG_WX_WIDGET_ADAPTER_HPP
#define BORG_WX_WIDGET_ADAPTER_HPP

#include <borg/tk/adapters_fwd.hpp>
#include <borg/tk/widget.hpp>
#include <borg/wx/traits.hpp>
#include <borg/types/dimension_type.hpp>
#include <borg/types/orientation_type.hpp>
#include <borg/types/update_mode.hpp>

namespace borg {
namespace tk {

using namespace types;
  
//---------------------------------------------------------------------------
template<class Derived>
struct widget_adapter<wx::traits, Derived>
{
  BORG_TK_WIDGET_TYPES( wx::traits )
//  BORG_WRAP_TRAITS(typename Traits::wrapper_traits)

  #define WINDOW_API(ret_type) inline ret_type
  #define WINDOW_CALL(fn_call) static_cast<Derived const *>(this)->get()->fn_call;

  #include "borg/wx/window_interface.ipp"

  #undef WINDOW_API
  #undef WINDOW_CALL
};
        
} // namespace tk
namespace wx { 
  
//  ADAPTER_ALIAS(traits, widget_adapter) 

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_WIDGET_ADAPTER_HPP
