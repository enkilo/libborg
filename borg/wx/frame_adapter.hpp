#ifndef WX_FRAME_ADAPTER_HPP
#define WX_FRAME_ADAPTER_HPP

#include <borg/tk/fwd.hpp>
#include <borg/tk/frame.hpp>
#include <borg/types/dimension_type.hpp>
#include <borg/wx/widget_adapter.hpp>

namespace borg {
namespace tk {

//---------------------------------------------------------------------------
template<class Derived>
class frame_adapter<wx::traits, Derived>
    : public widget_adapter<wx::traits, Derived>
{
public:
  BORG_TK_FRAME_TYPES(wx::traits)

  #define FRAME_API(ret_type) inline ret_type
  #define FRAME_CALL(fn_call) static_cast<Derived const *>(this)->get()->fn_call;

  #include "borg/wx/frame.ipp"
  
  #undef FRAME_API
  #undef FRAME_CALL
};
        
} // namespace tk
namespace wx {
//  ADAPTER_ALIAS(traits, frame_adapter)
} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif // WX_FRAME_ADAPTER_HPP
