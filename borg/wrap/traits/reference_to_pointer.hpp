//----------------------------------------------------------------------------
//! \file  reference_to_pointer.hpp
//! \brief Implements the borg::reference_to_pointer metafunction.
//! \svn  $Id: reference_to_pointer.hpp 12 2007-03-19 11:42:23Z nexbyte $
//----------------------------------------------------------------------------
#ifndef REFERENCE_TO_POINTER_HPP
#define REFERENCE_TO_POINTER_HPP

#include <boost/type_traits.hpp>
#include <boost/mpl/lambda.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping utilities.
//----------------------------------------------------------------------------
namespace borg {

  
//----------------------------------------------------------------------------
//! \name reference_to_pointer metafunction
//!
//! Make a pointer type from the supplied type. If the supplied type
//! is already a pointer, the resulting type stays the same.
//@{
//----------------------------------------------------------------------------
template<typename T>
  struct reference_to_pointer
{
  typedef T type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, reference_to_pointer, (T))
};

template<typename T>
  struct reference_to_pointer<T &>
{
  typedef T *const type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, reference_to_pointer, (T &))
};
//@}

} // end of namespace borg
#endif // REFERENCE_TO_POINTER_HPP
