//----------------------------------------------------------------------------
//! \file   reference_adapter.hpp  
//! \brief  Implements borg::reference_adapter class.
//!
//! \svn $Id: reference_adapter.hpp 35 2007-03-21 22:09:24Z nexbyte $
//----------------------------------------------------------------------------
#ifndef BORG_WRAP_REFERENCE_ADAPTER_HPP
#define BORG_WRAP_REFERENCE_ADAPTER_HPP

#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/wrap_concepts.hpp>
#include <borg/wrap/traits/make_reference.hpp>
#include <boost/utility/enable_if.hpp>

namespace borg {

using namespace boost::type_traits;

//----------------------------------------------------------------------------
//! Adapts basic wrapping methods like wrap_as_member to the internal 
//! the reference_f uses.
//----------------------------------------------------------------------------
template<
  class Derived,
  class Traits = typename Derived::wrap_traits
>
struct reference_adapter
{    
  BORG_WRAP_TRAITS(typename Traits)

/*  template<class ret>
  typename lazy_enable_if_c<
      ice_and<
          ice_or<
              is_reference<value_type>::value,
              is_reference<value_type>::value 
          >::value,
          is_reference<ret>::value 
      >::value,    
      ret
  >::type*/
  typename make_reference<value_type>::type
  get_reference() const
  {
    return addressof((*(Derived const *)this)->get());
  }
    
};

} // end of namespace borg
//----------------------------------------------------------------------------
#endif //ndef BORG_WRAP_REFERENCE_ADAPTER_HPP
