//----------------------------------------------------------------------------
//! \file  remove_const_reference.hpp
//! \brief Implements the borg::remove_const_reference metafunction.
//! \svn   $Id: remove_const_reference.hpp 35 2007-03-21 22:09:24Z nexbyte $
//----------------------------------------------------------------------------
#ifndef REMOVE_CONST_REFERENCE_HPP
#define REMOVE_CONST_REFERENCE_HPP

#include <boost/type_traits.hpp>

namespace borg 
{
//! Remove reference and const specifiers from the supplied type.
template<typename T>
  struct remove_const_reference
{
  typedef typename boost::remove_const<
    typename boost::remove_reference<T>::type
  >::type type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, remove_const_reference, (T))
};

template<typename T>
  struct remove_const_reference<const T &>
{
  typedef T type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, remove_const_reference, (const T &))
};

} // end of namespace borg

#endif // REMOVE_CONST_REFERENCE_HPP
