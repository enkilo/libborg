//----------------------------------------------------------------------------
//! \file remove_leftmost_const.hpp
//! \svn  $Id: remove_leftmost_const.hpp 35 2007-03-21 22:09:24Z nexbyte $
//!
//! Implements the borg::remove_leftmost_const metafunction.
//----------------------------------------------------------------------------
#ifndef REMOVE_LEFTMOST_CONST_HPP
#define REMOVE_LEFTMOST_CONST_HPP

#include <boost/type_traits.hpp>

namespace borg {

//----------------------------------------------------------------------------
//! Remove leftmost const specifier from the supplied type.
//----------------------------------------------------------------------------
template<typename T>
  struct remove_leftmost_const
{
  //! Defines T.
  typedef T type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, remove_leftmost_const, (T))
};

//----------------------------------------------------------------------------
//! Specialization for types which are const.
//----------------------------------------------------------------------------
template<typename T>
  struct remove_leftmost_const<const T>
{
  //! Defines T without const specifier.
  typedef T type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, remove_leftmost_const, (const T))
};

} // end of namespace borg
#endif //ndef REMOVE_LEFTMOST_CONST_HPP
