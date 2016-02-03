#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  add_leftmost_const.hpp
//! \brief Implements the borg::add_leftmost_const metafunction.
//! \svn   $Id: add_leftmost_const.hpp 66 2007-04-03 17:06:06Z nexbyte $
//----------------------------------------------------------------------------
#ifndef ADD_LEFTMOST_CONST_HPP
#define ADD_LEFTMOST_CONST_HPP

#include <boost/type_traits.hpp>

namespace borg {

//! Add const specifiers left to the supplied type.
template<typename T>
  struct add_leftmost_const
{
  //! Defines const T.
  typedef const T type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, add_leftmost_const, (T))
};

//! Specialization for types which are already const.
template<typename T>
  struct add_leftmost_const<const T>
{
  //! Defines const T.
  typedef const T type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, add_leftmost_const, (const T))
};

} // namespace borg
#endif //ndef ADD_LEFTMOST_CONST_HPP
