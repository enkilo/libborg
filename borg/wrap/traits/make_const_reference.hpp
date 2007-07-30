//----------------------------------------------------------------------------
//! \file make_const_reference.hpp
//! \svn  $Id: fit_word.hpp 34 2007-03-21 21:11:07Z nexbyte $
//----------------------------------------------------------------------------
#ifndef MAKE_CONST_REFERENCE_HPP
#define MAKE_CONST_REFERENCE_HPP

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>

#include <borg/wrap/traits/remove_const_reference.hpp>
#include <borg/wrap/traits/add_const_reference.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping objects.
//----------------------------------------------------------------------------
namespace borg {

  
//----------------------------------------------------------------------------
//! Make a const reference type from the supplied type. 
//! If the supplied type is already a reference, then the referencee
//! is made a const.
//----------------------------------------------------------------------------
template<typename T>
  struct make_const_reference
{
  typedef typename add_const_reference<
    typename remove_const_reference<T>::type
  >::type type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_const_reference, (T))
};

} // end of namespace borg
#endif //ndef MAKE_CONST_REFERENCE_HPP
