//----------------------------------------------------------------------------
//! \file   is_basically_same.hpp
//! \brief  Provides the is_basically_same metafunction.
//!
//! \svn $Id: is_basically_same.hpp 12 2007-03-19 11:42:23Z nexbyte $
//----------------------------------------------------------------------------
#ifndef IS_BASICALLY_SAME_HPP
#define IS_BASICALLY_SAME_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/detail/bool_trait_def.hpp>

namespace borg {


//! Coreementation details.
namespace detail
{
  using namespace type_traits;
  
  //! Is type T basically the same as type U?
  template<typename T, typename U>
    struct is_basically_same_impl
  {
    BOOST_STATIC_CONSTANT(bool, value =
                          (is_same<
                             typename remove_const_reference<T>::type,
                             typename remove_const_reference<U>::type
                           >::value));
  };
}

//----------------------------------------------------------------------------
//! Declare the is_basically_same<T, U> metafunction.
//----------------------------------------------------------------------------
template<typename T, typename U>
  struct is_basically_same
    BOOST_TT_AUX_BOOL_C_BASE((detail::is_basically_same_impl<T, U>::value))
{
  BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL((detail::is_basically_same_impl<T, U>::value))
  BOOST_MPL_AUX_LAMBDA_SUPPORT(2, is_basically_same, (T, U))
};

} // namespace borg

#include <boost/type_traits/detail/bool_trait_undef.hpp>
//----------------------------------------------------------------------------
#endif // IS_BASICALLY_SAME_HPP
