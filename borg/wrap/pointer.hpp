#ifndef POINTER_HPP
#define POINTER_HPP

#include <borg/wrap/wrapper.hpp>
#include <borg/wrap/pointer_adapter.hpp>
#include <borg/wrap/pointer_facade.hpp>

namespace borg {
 
//---------------------------------------------------------------------------
template<
    class ValueT,
    class Traits = wrap_traits<ValueT *>,
    template<class, class> class adapter = pointer_adapter 
>
struct pointer 
    : public wrapper< ValueT *, Traits,
                      wrap_as_member<ValueT *, Traits>,
                      pointer_facade,
                      adapter >
{
  BORG_WRAP_TRAITS(typename Traits)

  typedef wrapper< ValueT *,
                   Traits,
                   wrap_as_member<ValueT *, Traits>,
                   pointer_facade,
                   adapter >
  wrapper_type;

  pointer() : wrapper_type(0) {}
  pointer(init_type ptr) : wrapper_type(ptr) {}  
};

}// end of namespace borg
//---------------------------------------------------------------------------
#endif // POINTER_HPP
