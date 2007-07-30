#ifndef BORG_WX_BITMAP_ADAPTER_HPP
#define BORG_WX_BITMAP_ADAPTER_HPP

#include <wx/wx.h>

#include <borg/tk/adapters_fwd.hpp>
#include <borg/tk/bitmap.hpp>
#include <borg/wx/traits.hpp>

namespace borg {
namespace tk {

//---------------------------------------------------------------------------
template<class Derived>
class bitmap_adapter<wx::traits, Derived>
{
public:
  BORG_TK_BITMAP_TYPES( wx::traits )
//  BITMAP_TRAITS(typename Traits)

  typedef Derived const derived_type;

  #define BITMAP_API(ret_type) inline ret_type
  #define BITMAP_CALL(fn_call) const_cast<bitmap_type *>(static_cast<derived_type *>(this)->get())->fn_call

  #include "borg/wx/bitmap.ipp"

  #undef BITMAP_API
  #undef BITMAP_CALL
};

} // namespace tk
namespace wx { 
//  ADAPTER_ALIAS(traits, bitmap_adapter) 
} // namespace wx
} // namespace borg


//---------------------------------------------------------------------------
#endif // BORG_WX_BITMAP_ADAPTER_HPP
