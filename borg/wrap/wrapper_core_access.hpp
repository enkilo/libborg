//----------------------------------------------------------------------------
//! \file  wrapper_core_access.hpp  
//! \brief Implements borg::wrapper_core_access.
//! \svn   $Id: wrapper_core_access.hpp 13 2007-03-19 11:55:21Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WRAPPER_CORE_ACCESS_HPP
#define WRAPPER_CORE_ACCESS_HPP

#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>

//#include "wrap/concepts/wrapper_core_concept.hpp"

namespace borg {

using boost::function_requires;
  
//----------------------------------------------------------------------------
class wrapper_core_access
{
public:  
  template<template<class, class> class WrapperCore, class Value, class Traits>
  static typename Traits::unwrap_type
  get(const WrapperCore<Value, Traits> &w)
    { return w.get(); }

  template<template<class, class> class WrapperCore, class Value, class Traits>
  static boost::lazy_enable_if_c<Traits::is_mutable, typename Traits::value_type &>
  get(WrapperCore<Value, Traits> &w)
    { return w.get(); }

  /// Get const reference to wrapee.
/*  template<typename WrapperCoreT>
  static typename WrapperCoreT::unwrap_type
  get(WrapperCoreT const &w) { return w.get(); }
  
  /// Get reference to wrapee.
  template<typename WrapperCoreT>
  static typename WrapperCoreT::unwrap_type
  *get(WrapperCoreT const &w) { return w.get(); }*&
  
  /// Get reference to wrapee.
  template<typename WrapperCoreT>
  static typename WrapperCoreT::value_type &
  get(WrapperCoreT &w) { return w.get(); }*/
  template<class Wrapper>
  static typename Wrapper::unwrap_type
  get(const Wrapper &w)
  { return const_cast<Wrapper *>(boost::addressof(w))->get(); }

  template<class Wrapper>
  static typename Wrapper::unwrap_type
  get(Wrapper &w)
  { return w.get(); }

  
  /// Assign new wrapee to mutable wrapper core.
  template<typename WrapperCoreT, typename ValueT>
  static void
  set(WrapperCoreT &w, ValueT v) 
  {
//    function_requires< Mutable_WrapperCoreConcept< WrapperCoreT, ValueT > >();
    w.set(v); 
  }

  template<typename WrapperCoreT, typename ValueT>
  static void
  set(WrapperCoreT *w, ValueT v) 
  {
//    function_requires< Mutable_WrapperCoreConcept< WrapperCoreT, ValueT > >();
    return w->set(v); 
  }
};  

} // namespace borg
//----------------------------------------------------------------------------
#endif //ndef WRAPPER_CORE_ACCESS_HPP
