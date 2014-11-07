//----------------------------------------------------------------------------
//! \file  add_const_reference.hpp
//! \brief Implements the borg::add_const_reference metafunction.
//! \svn   $Id: add_const_reference.hpp 39 2007-03-22 23:11:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef ADD_CONST_REFERENCE_HPP
#define ADD_CONST_REFERENCE_HPP

#include <boost/type_traits.hpp>

namespace borg {

//! Add const and reference specifiers to the supplied type.
template<typename T>
  struct add_const_reference
{
  //! Defines const-reference to T.
  typedef T const &type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, add_const_reference, (T))
};

// Specialization for types which are already const.
template<typename T>
  struct add_const_reference<T const>
{
  // Add reference specifier.
  typedef T &type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, add_const_reference, (T const))
};

// Specialization for types which are already a reference.
template<typename T>
  struct add_const_reference<T &>
{
  // Add const specifier.
  typedef T const type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, add_const_reference, (T &))
};

} // namespace borg
#endif //ndef ADD_CONST_REFERENCE_HPP
