//----------------------------------------------------------------------------
//! \file  wrapper_impl_concept.hpp  
//! \brief Implements wrapper concepts.
//!
//! \svn $Id: wrapper_impl_concept.hpp 37 2007-03-22 02:16:30Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WRAPPER_CORE_CONCEPT_HPP
#define WRAPPER_CORE_CONCEPT_HPP

#include <boost/concept_archetype.hpp>
#include <borg/wrap/wrapper_core_access.hpp>

namespace borg {

//----------------------------------------------------------------------------
//! Explicit non-mutable wrapper concept.
//----------------------------------------------------------------------------
template<typename WrapperCore,
         typename ValueT = typename WrapperCore::value_type,
         typename WrapT = typename WrapperCore::wrap_type,
         typename UnwrapT = typename WrapperCore::unwrap_type>

struct WrapperCoreConcept
{
  typedef ValueT value_type;
  typedef WrapT wrap_type;
  
  void constraints()
  {
    const_constraints();
  }
  
  void const_constraints()
  {
//    wrap_type &v = static_object<wrap_type>::get();
//    const WrapperCore w(v);
    WrapperCore const &w = boost::static_object<WrapperCore const>::get();
    value_type u = borg::wrapper_core_access::get(w);
    boost::ignore_unused_variable_warning(u);
  }
};

//----------------------------------------------------------------------------
//! Explicit mutable wrapper concept.
//----------------------------------------------------------------------------
template<typename Mutable_WrapperCore,
         typename ValueT = typename Mutable_WrapperCore::value_type,
         typename WrapT = typename Mutable_WrapperCore::wrap_type>

struct Mutable_WrapperCoreConcept
{
  typedef ValueT value_type;
  typedef WrapT wrap_type;
  
  void constraints()
  {
    wrap_type v1, v2;
    Mutable_WrapperCore w(v1);
    w.set(v2);

    const_constraints();
  }

  void const_constraints()
  {
    boost::function_requires<
        WrapperCoreConcept<Mutable_WrapperCore, const ValueT, WrapT> 
    >();
  }
};

} // end of namespace borg
//----------------------------------------------------------------------------
#endif //ndef WRAPPER_CORE_CONCEPT_HPP
