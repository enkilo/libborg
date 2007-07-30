//----------------------------------------------------------------------------
//! \file   convertible.hpp
//! \brief  Implements borg::core::convertible
//!
//! \svn $Id: explicit_wrapper.hpp 16 2007-03-19 19:38:49Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WRAP_CORE_CONVERTIBLE_HPP
#define WRAP_CORE_CONVERTIBLE_HPP

#include <boost/concept_check.hpp>
#include <boost/utility/enable_if.hpp>
#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/wrap_concepts.hpp>

namespace borg {
namespace core {

//----------------------------------------------------------------------------
//! Wrapper core interface for base types which are convertible to wrapee.
//----------------------------------------------------------------------------
template< class base, class traits = wrap_traits<base> >
struct convertible
{
  //! \name Types from traits:
  //@{
  BORG_WRAP_TRAITS(typename traits)
  //@}
  
  //! Checking whether wrap_type is constructible from init_type.
//  BOOST_CLASS_REQUIRE2(wrap_type, init_type, wrap, ConvertibleConcept);
  //! Checking whether wrap_type is returnable as unwrap_type.
//  BOOST_CLASS_REQUIRE2(wrap_type, unwrap_type, wrap, ReturnableAsConcept);
  
  //! Define ourselves.
  typedef convertible<base, traits> this_type;
  typedef base base_type;
  
  //! Return wrapee.
  const wrap_type &
  get() const { return *static_cast<base *>(this); }

  //! Return wrapee.
  wrap_type &
  get() { return *static_cast<base *>(this); }
};

} // namespace core
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef WRAP_CORE_CONVERTIBLE_HPP
