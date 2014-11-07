//----------------------------------------------------------------------------
//! \file   pointer_adapter.hpp  
//! \brief  Implements borg::pointer_adapter class.
//!
//! \svn $Id: pointer_adapter.hpp 35 2007-03-21 22:09:24Z nexbyte $
//----------------------------------------------------------------------------
#ifndef POINTER_ADAPTER_HPP
#define POINTER_ADAPTER_HPP

#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/wrap_concepts.hpp>
#include <borg/wrap/traits/make_pointer.hpp>
#include <boost/utility/enable_if.hpp>

namespace borg {

using namespace boost::type_traits;

//----------------------------------------------------------------------------
//! Adapts basic wrapping methods like wrap_as_member to the internal 
//! the pointer_f uses.
//----------------------------------------------------------------------------
template<
  class Derived,
  class Traits = typename Derived::wrap_traits
>
struct pointer_adapter
{    
  BORG_WRAP_TRAITS(typename Traits)

/*  template<class ret>
  typename lazy_enable_if_c<
      ice_and<
          ice_or<
              is_pointer<value_type>::value,
              is_reference<value_type>::value 
          >::value,
          is_pointer<ret>::value 
      >::value,    
      ret
  >::type*/
  typename make_pointer<value_type>::type
  get_pointer() const
  {
    return addressof((*(Derived const *)this)->get());
  }
    
};

} // end of namespace borg
//----------------------------------------------------------------------------
#endif //ndef POINTER_ADAPTER_HPP
