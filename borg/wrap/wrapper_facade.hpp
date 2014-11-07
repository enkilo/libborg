//----------------------------------------------------------------------------
//! \file  wrapper_facade.hpp  
//! \brief Implements borg::wrapper_facade and its specialisations.
//! \svn   $Id: wrapper_facade.hpp 13 2007-03-19 11:55:21Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WRAPPER_FACADE_HPP
#define WRAPPER_FACADE_HPP

#include <boost/type_traits.hpp>
#include <boost/concept_check.hpp>
#include <boost/utility/enable_if.hpp>

#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/concepts/wrapper_core_concept.hpp>
#include <borg/wrap/wrapper_core_access.hpp>
#include <borg/wrap/pointer_facade.hpp>

namespace borg {

struct empty {};  
  
//----------------------------------------------------------------------------
//! Provides implicit conversion and (if mutable) assignment operators.
//----------------------------------------------------------------------------
template<class Derived, class Traits>
struct wrapper_facade
    : public boost::mpl::if_<
        typename boost::is_pointer<typename Traits::value_type>, 
        pointer_facade<Derived, Traits>, empty >::type

{
  //! \name Typedefs from the traits.
  //@{
  BORG_WRAP_TRAITS(typename Traits)
  //@}

  //! \name Concept checks.
  //@{
//  BOOST_CLASS_REQUIRE3(Derived, value_type, wrap_type, wrap, WrapperCoreConcept);
  //@}

  //! Implicit conversion to value_type
  operator value_type() const
  {
//    return const_cast<derived *>(reinterpret_cast<const derived *>(this))->get();
//    return wrapper_core_access::get(*reinterpret_cast<derived const *>(this));
//   return wrapper_core_access::get(static_cast<Derived const *const>(this));
   return wrapper_core_access::get(*reinterpret_cast<Derived const *const>(this));
  }

  operator bool() const
  {
    return wrapper_core_access::get(*reinterpret_cast<Derived const *const>(this));
    
  }
  
  //! Assignment operator, enabled only if param is assignable to value_type.
  template<class ValueU>
  Derived &
  operator=(typename boost::lazy_enable_if<
                is_assignable_to<ValueU, value_type>,
                typename const_traits::param_type
            >::type w)
  { 
//    static_cast<Derived *>(this)->set(w);
    wrapper_core_access::set(static_cast<Derived *const>(this), w);
    return *static_cast<Derived *>(this);
  }
  
  //! Arrow operator, enabled only if value_type is a pointer.
/*  typename boost::lazy_enable_if< boost::is_pointer<value_type>, boost::remove_const<value_type> >::type
  operator->() const
  {
    return wrapper_core_access::get(*reinterpret_cast<Derived const *const>(this));
  }*/
};

} // namespace borg
//----------------------------------------------------------------------------
#endif //ndef WRAPPER_FACADE_HPP
