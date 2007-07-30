//----------------------------------------------------------------------------
//! \file   is_assignable_to.hpp
//! \brief  Provides the borg::is_assignable_to metafunction.
//!
//! \svn $Id: is_assignable_to.hpp 12 2007-03-19 11:42:23Z nexbyte $
//----------------------------------------------------------------------------
#ifndef IS_ASSIGNABLE_TO_HPP
#define IS_ASSIGNABLE_TO_HPP

#include "boost/type_traits.hpp"
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace borg {

//! Coreementation details.
namespace detail
{
  using namespace type_traits;
  
  //! Is type T assignable to type U?
  template<typename T, typename U, bool trivially> 
    struct is_assignable_to_impl
  {
    BOOST_STATIC_CONSTANT(bool, value =
                          (ice_and< is_mutable<U>::value,
                                    is_convertible<T, U>::value >::value));
  };
}

//! Declare the is_assignable_to<T, trivially> metafunction.
template<typename T, typename U, bool trivially = false>
  struct is_assignable_to
    BOOST_TT_AUX_BOOL_C_BASE((detail::is_assignable_to_impl<T, U, trivially>::value))
{
  BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL((detail::is_assignable_to_impl<T, U, trivially>::value))
  BOOST_MPL_AUX_LAMBDA_SUPPORT(2, is_assignable_to, (T, U))
};

} // namespace borg
//----------------------------------------------------------------------------
#include "boost/type_traits/detail/bool_trait_undef.hpp"
#endif // IS_ASSIGNABLE_TO_HPP
