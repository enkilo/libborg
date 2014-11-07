//----------------------------------------------------------------------------
//! \file  make_reference.hpp
//! \brief Implements the borg::make_reference metafunction.
//! \svn  $Id: make_reference.hpp 12 2007-03-19 11:42:23Z nexbyte $
//----------------------------------------------------------------------------
#ifndef MAKE_REFERENCE_HPP
#define MAKE_REFERENCE_HPP

#include <boost/type_traits.hpp>
#include <boost/mpl/lambda.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping utilities.
//----------------------------------------------------------------------------
namespace borg {

  
//----------------------------------------------------------------------------
//! \name make_reference metafunction
//!
//! Make a reference type from the supplied type. If the supplied type
//! is already a reference, the resulting type stays the same.
//@{
//----------------------------------------------------------------------------
template<typename T>
  struct make_reference
{
  typedef T &type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_reference, (T))
};

template<typename T>
  struct make_reference<T &>
{
  typedef T &type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_reference, (T &))
};
//@}

} // end of namespace borg
#endif // MAKE_REFERENCE_HPP
