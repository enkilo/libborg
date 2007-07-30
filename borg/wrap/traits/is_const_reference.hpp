//----------------------------------------------------------------------------
//! \file fit_word.hpp
//! \svn  $Id: fit_word.hpp 34 2007-03-21 21:11:07Z nexbyte $
//----------------------------------------------------------------------------
#ifndef IS_CONST_REFERENCE_HPP
#define IS_CONST_REFERENCE_HPP

#include <boost/type_traits.hpp>
#include <boost/type_traits/detail/bool_trait_def.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping objects.
//----------------------------------------------------------------------------
namespace borg {

  
//! Coreementation details.
namespace detail {

//----------------------------------------------------------------------------
//! Identify const reference types.
//----------------------------------------------------------------------------
template<typename T> 
  struct is_const_reference_impl
{
  BOOST_STATIC_CONSTANT(
      bool, value =
        (type_traits::ice_and<
            is_reference<T>::value,
            is_const<typename remove_reference<T>::type>::value
         >::value));
};

} // namespace detail
  
//----------------------------------------------------------------------------
//! Declare the is_const_reference<T> metafunction.
//----------------------------------------------------------------------------
BOOST_TT_AUX_BOOL_TRAIT_DEF1(
    is_const_reference, T,
    ::borg::detail::is_const_reference_impl<T>::value)

} // namespace borg  
  
#include <boost/type_traits/detail/bool_trait_undef.hpp>
#endif //ndef IS_CONST_REFERENCE_HPP
